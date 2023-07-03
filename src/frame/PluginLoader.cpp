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
                auto modlue         = Interfaces::model_fromjson(
                  {{"objectName", "hmodule"},
                           {"name", "test100"},
                           {"displayName", QObject::tr("test1")},
                           {"descrption", QObject::tr("test33433")},
                           {"models", std::invoke([]() -> QJsonArray {
                        QJsonArray array;
                        array.append(QJsonObject{{"objectName", "base"},
                                                         {"name", "test2"},
                                                         {"displayName", QObject::tr("test2")},
                                                         {"descrption", QObject::tr("test9999")},
                                                         {"searchpatterns", std::invoke([]() -> QJsonArray {
                                                      return {"sss", "sss", "bbb"};
                                                  })}});
                        return array;
                    })}});
                auto topModule = pd->topModule();
                Interfaces::insert_model(topModule, modlue, "test1");
                qDebug() << topModule;
                Q_EMIT urlLoader(pd->mainLink());
            }
        }
    }
}
