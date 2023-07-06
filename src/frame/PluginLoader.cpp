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
    QTimer::singleShot(0, [this] { load_plugins(); });
}

void
PluginLoader::load_plugins()
{
    QDir plugindir(QCoreApplication::applicationDirPath());
    plugindir.cd("plugins");
    if (plugindir.exists()) {
        for (QString filename : plugindir.entryList(QDir::Files)) {
            QPluginLoader pluginLoader(plugindir.absoluteFilePath(filename));
            QObject *plugin = pluginLoader.instance();
            if (plugin) {
                PluginInterface *pd = qobject_cast<PluginInterface *>(plugin);
                auto topModule      = pd->topModule();
                m_modules.append(topModule);
                Q_EMIT modulesChanged();
                // Interfaces::insert_model(topModule, modlue, "test1");
                qDebug() << topModule;
                Q_EMIT urlLoader(pd->mainLink());
            }
        }
    }
}
