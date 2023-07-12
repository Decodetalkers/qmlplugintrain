#include "pluginc.h"
#include "modulemodel.h"
#include <QJsonArray>

#include <QQmlApplicationEngine>
#include <QUrl>

PluginC::PluginC()
{
}

QString
PluginC::pluginName() const
{
    return "PluginC";
}

Interfaces::BaseModule *
PluginC::topModule() const
{
    return Interfaces::BaseModule::fromJson({{"objectName", "vmodule"},
                                             {"name", "test2"},
                                             {"displayName", QObject::tr("testc")},
                                             {"icon", "kate"},
                                             {"description", QObject::tr("test33433")},
                                             {"models", std::invoke([]() -> QJsonArray {
                                                  QJsonArray array;
                                                  return array;
                                              })},
                                             {"isSpecial", true}});
}
