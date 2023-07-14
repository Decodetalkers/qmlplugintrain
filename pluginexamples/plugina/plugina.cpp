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

Interfaces::BaseModule *
PluginA::topModule() const
{
    return Interfaces::BaseModule::fromJson(
      {{"objectName", "hmodule"},
       {"name", "testa"},
       {"displayName", QObject::tr("testa")},
       {"icon", "vlc"},
       {"models", std::invoke([]() -> QJsonArray {
            QJsonArray array;
            array.append(QJsonObject{{"objectName", "base"},
                                     {"name", "test2"},
                                     {"displayName", QObject::tr("test2")},
                                     {"description", QObject::tr("test9999")},
                                     {"searchpatterns", std::invoke([]() -> QJsonArray {
                                          return {"sss", "sss", "bbb"};
                                      })},
                                     {"url", "qrc:/qml/entrance.qml"}});
            array.append(QJsonObject{{"objectName", "base"},
                                     {"name", "test3"},
                                     {"displayName", QObject::tr("test333")},
                                     {"description", QObject::tr("test9999")},
                                     {"searchpatterns", std::invoke([]() -> QJsonArray {
                                          return {"sss", "sss", "bbb"};
                                      })},
                                     {"url", "qrc:/qml/entrancec.qml"}});
            return array;
        })}});
}
