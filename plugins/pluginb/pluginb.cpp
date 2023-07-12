#include "pluginb.h"
#include "GlobalConst.h"
#include "modulemodel.h"
#include <QJsonArray>

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

Interfaces::BaseModule *
PluginA::topModule() const
{
    return Interfaces::BaseModule::fromJson(
      {{"objectName", "vmodule"},
       {"name", "test2"},
       {"displayName", QObject::tr("testb")},
       {"description", QObject::tr("test33433")},
       {"models", std::invoke([]() -> QJsonArray {
            QJsonArray array;
            array.append(QJsonObject{{"objectName", "base"},
                                     {"name", "test2ff22"},
                                     {"displayName", QObject::tr("ffff232")},
                                     {"description", QObject::tr("test9999")},
                                     {"searchpatterns", std::invoke([]() -> QJsonArray {
                                          return {"sss", "sss", "bbb"};
                                      })},
                                     {"url", "qrc:/qml/entranceb.qml"}});
            array.append(QJsonObject{{"objectName", "base"},
                                     {"name", "test44444444"},
                                     {"displayName", QObject::tr("test32ee32")},
                                     {"description", QObject::tr("test9999")},
                                     {"searchpatterns", std::invoke([]() -> QJsonArray {
                                          return {"sss", "sss", "bbb"};
                                      })},
                                     {"url", "qrc:/qml/entrancef.qml"}});
            return array;
        })}});
}
