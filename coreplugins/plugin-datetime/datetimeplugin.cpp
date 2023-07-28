#include "datetimeplugin.h"
#include "modulemodel.h"
#include <QJsonArray>

#include <QQmlApplicationEngine>
#include <QUrl>

PluginDatetime::PluginDatetime()
{
}

QString
PluginDatetime::pluginName() const
{
    return "PluginDatetime";
}

Interfaces::BaseModule *
PluginDatetime::topModule() const
{
    return Interfaces::BaseModule::fromJson({
      {"objectName", "hmodule"},
      {"name", "DateTime"},
      {"displayName", QObject::tr("Date and Time")},
      {"icon", "kate"},
      {"models", std::invoke([]() -> QJsonArray {
           QJsonArray array;
           array.append(QJsonObject({{"objectName", "base"},
                                     {"name", "timesettings"},
                                     {"displayName", tr("Time Settings")},
                                     {"description", tr("About set Time")},
                                     {"url", "qrc:/Datetime/qml/timesettings.qml"}}));
           return array;
       })},
    });
}
