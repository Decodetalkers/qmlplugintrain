#include "plugina.h"
#include "GlobalConst.h"

#include <QQmlApplicationEngine>
#include <QUrl>

void
registerGlobalTypes()
{
    qmlRegisterSingletonType<GlobalConst>(
      "PluginA.Global", 1, 0, "GlobalConst", [](QQmlEngine *, QJSEngine *) -> QObject * {
          return new GlobalConst;
      });
}

PluginA::PluginA()
{
    registerGlobalTypes();
}

QString
PluginA::pluginName() const
{
    return "PluginA";
}

QUrl
PluginA::mainLink() const
{
    return QUrl("qrc:/qml/entrance.qml");
}
