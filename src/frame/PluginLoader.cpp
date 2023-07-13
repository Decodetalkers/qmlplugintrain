#include "PluginLoader.h"

#include <QJsonArray>
#include <baseInterface.h>

#include <QCoreApplication>
#include <QDir>
#include <QPluginLoader>
#include <QTimer>
#include <QUrl>

PluginLoader::PluginLoader(QObject *parent)
  : QObject(parent)
{
    load_plugins();
}

void
PluginLoader::load_plugins()
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
            m_modules.append(topModule);
            plugin->deleteLater();
        }

        Q_EMIT modulesChanged();
    }
}
