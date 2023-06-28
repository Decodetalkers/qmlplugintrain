#include <baseInterface.h>

#include <QApplication>
#include <QDir>
#include <QGuiApplication>
#include <QIcon>
#include <QPluginLoader>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QSettings>

void
load_plugins()
{
    QDir plugindir(QCoreApplication::applicationDirPath());
    plugindir.cd("plugins");
    if (plugindir.exists()) {
        for (QString filename : plugindir.entryList(QDir::Files)) {
            QPluginLoader pluginLoader(plugindir.absoluteFilePath(filename));
            QObject *plugin = pluginLoader.instance();
            if (plugin) {
                PluginInterface *pd = qobject_cast<PluginInterface *>(plugin);
                qDebug() << pd->mainLink();
            }
        }
    }
}

int
main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Marine");
    QGuiApplication::setOrganizationName("QtProject");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(u"qrc:/Marine/qml/main.qml"_qs);
    QObject::connect(
      &engine,
      &QQmlApplicationEngine::objectCreated,
      &app,
      [url](QObject *obj, const QUrl &objUrl) {
          if (!obj && url == objUrl)
              QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);

    engine.load(url);
    load_plugins();

    return app.exec();
}
