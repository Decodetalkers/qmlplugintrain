#include "PluginLoader.h"

#include <QApplication>
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QSettings>

void
registerGlobalTypes()
{
    qmlRegisterSingletonType<PluginLoader>(
      "Marine.Global", 1, 0, "PluginLoader", [](QQmlEngine *, QJSEngine *) -> QObject * {
          return new PluginLoader;
      });
}

int
main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Marine");
    QGuiApplication::setOrganizationName("QtProject");
    QGuiApplication app(argc, argv);

    registerGlobalTypes();
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

    return app.exec();
}