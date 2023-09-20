#include "PluginLoader.h"

#include <QApplication>
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QSettings>

#include <DLog>

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
    engine.addImportPath(QString("%1/qmlplugin").arg((QCoreApplication::applicationDirPath())));

    Dtk::Core::DLogManager::setLogFormat(
      "%{time}{yy-MM-ddTHH:mm:ss.zzz} [%{type}] [%{category}] <%{function}> %{message}");

    Dtk::Core::DLogManager::registerConsoleAppender();
    QQuickStyle::setStyle("Chameleon");

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    const QUrl url = QUrl("qrc:/Marine/qml/main.qml");
#else
    const QUrl url(u"qrc:/Marine/qml/main.qml"_qs);
#endif
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
