#include "plugina.h"
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

QUrl
PluginA::mainLink() const
{
    return QUrl("qrc:/qml/entrance.qml");
}

Interfaces::ModuleModel
PluginA::topModule() const
{
    return Interfaces::model_fromjson(
      {{"objectName", "hmodule"},
       {"name", "test1"},
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
}
