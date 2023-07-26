#include "PluginLoader.h"

#include <baseInterface.h>

#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
#include <QRegularExpression>
#include <QUrl>

PluginModel::PluginModel(QObject *parent)
  : QAbstractListModel(parent)
{
}

void
PluginModel::clear()
{
    beginResetModel();
    m_results.clear();
    endResetModel();
}

void
PluginModel::insert(Interfaces::SearchResult &result)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_results.push_back(result);
    endInsertRows();
}

QVariant
PluginModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Display:
        return m_results[index.row()].display;
    case Routine:
        return QVariant::fromValue(m_results[index.row()].routine);
    default:
        return QVariant();
    }
}

int
PluginModel::rowCount(const QModelIndex &) const
{
    return m_results.count();
}

QHash<int, QByteArray>
PluginModel::roleNames() const
{
    static const QHash<int, QByteArray> roles{{Display, "displayName"}, {Routine, "routine"}};
    return roles;
}

PluginLoader::PluginLoader(QObject *parent)
  : QObject(parent)
  , m_model(new PluginModel(this))
  , m_proxyModel(new QSortFilterProxyModel(this))
{
    loadPlugins();
    initModel();
    setProxy();
}

void
PluginLoader::setProxy()
{
    m_proxyModel->setSourceModel(m_model);
}

void
PluginLoader::getModel(const QString &filter)
{
    if (filter.isEmpty()) {
        initModel();
    }
    if (filter.contains("\\")) {
        return;
    }
    auto re = QRegularExpression(filter, QRegularExpression::CaseInsensitiveOption);
    m_proxyModel->setFilterRegularExpression(re);

    Q_EMIT searchPatternChanged();
}

void
PluginLoader::resetModel()
{
    getModel("");
}

void
PluginLoader::initModel()
{
    m_model->clear();
    for (auto searchResult : getAllRoutine()) {
        m_model->insert(searchResult);
    }
    Q_EMIT searchPatternChanged();
}

QList<Interfaces::SearchResult>
PluginLoader::getAllRoutine()
{
    auto modelLen = m_modules.length();
    if (modelLen == 0) {
        return {};
    }
    QList<Interfaces::SearchResult> results;

    for (int index = 0; index < modelLen; index++) {
        for (auto routine : m_modules[index]->getAllRoutine()) {
            QList<int> routinetop = routine.routine;
            routinetop.push_front(index);
            results.push_back({routine.display, routinetop});
        }
    }
    return results;
}

void
PluginLoader::loadPlugins()
{
    QDir plugindir(QCoreApplication::applicationDirPath());
    plugindir.cd("pluginexamples");
    QList<PluginInterface *> plugins;
    if (plugindir.exists()) {
        for (QString filename : plugindir.entryList(QDir::Files)) {
            QPluginLoader pluginLoader(plugindir.absoluteFilePath(filename));
            QObject *plugin = pluginLoader.instance();
            if (plugin) {
                PluginInterface *pd = qobject_cast<PluginInterface *>(plugin);
                plugins.push_back(pd);
            }
        }
        // TODO: this just handle position on the top
        std::sort(plugins.begin(),
                  plugins.end(),
                  [](const PluginInterface *v1, const PluginInterface *v2) -> bool {
                      if (!v2->position().has_value()) {
                          return true;
                      }
                      if (!v1->position().has_value()) {
                          return false;
                      }
                      uint v2pos = v2->position().value();
                      uint v1pos = v1->position().value();
                      return v1pos < v2pos;
                  });
        for (auto plugin : plugins) {
            auto topModule = plugin->topModule();
            if (topModule->upModule().has_value()) {
                continue;
            }
            m_modules.append(topModule);
            plugins.removeOne(plugin);
            plugin->deleteLater();
        }

        u_int plugin_count = plugins.length();
        u_int plugin_count_later;
        if (plugin_count == 0) {
            Q_EMIT modulesChanged();
            return;
        }
        do {
            plugin_count = plugins.length();
            for (auto module : m_modules) {
                for (auto plugin : plugins) {
                    auto childModule = plugin->topModule();
                    if (Interfaces::insertModel(
                          module, childModule, childModule->upModule().value()) == 0) {
                        plugins.removeOne(plugin);
                        plugin->deleteLater();
                    }
                }
            }
            plugin_count_later = plugins.length();
        } while (plugin_count_later < plugin_count);

        Q_EMIT modulesChanged();
    }
}
