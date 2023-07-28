#include "plugine.h"
#include "modulemodel.h"
#include <QJsonArray>

#include <QQmlApplicationEngine>
#include <QUrl>

PluginE::PluginE()
{
}

QString
PluginE::pluginName() const
{
    return "PluginE";
}

Interfaces::BaseModule *
PluginE::topModule() const
{
    return Interfaces::BaseModule::fromJson({{"objectName", "hmodule"},
                                             {"name", "teste"},
                                             {"displayName", QObject::tr("teste")},
                                             {"icon", "kate"},
                                             {"description", QObject::tr("test33433")},
                                             {"models", std::invoke([]() -> QJsonArray {
                                                  QJsonArray array;
                                                  return array;
                                              })},
                                             {"isSpecial", true}});
}
