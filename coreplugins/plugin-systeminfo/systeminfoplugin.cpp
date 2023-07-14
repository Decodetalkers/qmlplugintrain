#include "systeminfoplugin.h"
#include "AboutMyPcBackendObject.h"
#include "LicencesBackendObject.h"
#include "modulemodel.h"
#include <QJsonArray>

#include <QQmlApplicationEngine>
#include <QUrl>

void
registerGlobalTypes()
{
    qmlRegisterSingletonType<AboutMyPcBackendObject>(
      "SystemInfo.Base", 1, 0, "AboutMyPc", [](QQmlEngine *, QJSEngine *) -> QObject * {
          return new AboutMyPcBackendObject;
      });
    qmlRegisterSingletonType<AboutMyPcBackendObject>(
      "SystemInfo.Base", 1, 0, "LicenseObject", [](QQmlEngine *, QJSEngine *) -> QObject * {
          return new LicenseBackendObject;
      });
}

PluginSystemInfo::PluginSystemInfo()
{
    registerGlobalTypes();
}

QString
PluginSystemInfo::pluginName() const
{
    return "SystemInfo";
}

Interfaces::BaseModule *
PluginSystemInfo::topModule() const
{
    return Interfaces::BaseModule::fromJson(
      {{"objectName", "hmodule"},
       {"name", "SystemInfo"},
       {"displayName", QObject::tr("SystemInfo")},
       {"icon", "preferences-system"},
       {"models", std::invoke([]() -> QJsonArray {
            QJsonArray array;
            array.append(
              QJsonObject{{"objectName", "base"},
                          {"name", "aboutpc"},
                          {"displayName", QObject::tr("About This Pc")},
                          {"description", QObject::tr("show the info of pc")},
                          {"searchpatterns", std::invoke([]() -> QJsonArray { return {}; })},
                          {"url", "qrc:/qml/aboutpc.qml"}});
            array.append(QJsonObject{
              {"objectName", "vmodule"},
              {"name", "licenses"},
              {"displayName", QObject::tr("Agreements and Privacy Policy")},
              {"models", std::invoke([]() -> QJsonArray {
                   QJsonArray array;
                   array.append(
                     QJsonObject{{"objectName", "base"},
                                 {"name", "editlicense"},
                                 {"displayName", QObject::tr("Edition License")},
                                 {"description", QObject::tr("Edition License")},
                                 {"icon", "dcc_version"},
                                 {"searchpatterns", std::invoke([]() -> QJsonArray { return {}; })},
                                 {"url", "qrc:/qml/gnulicense.qml"}});
                   array.append(
                     QJsonObject{{"objectName", "base"},
                                 {"name", "privacyPolicy"},
                                 {"displayName", QObject::tr("Privacy Policy")},
                                 {"description", QObject::tr("privacyPolicy")},
                                 {"icon", "dcc_privacy_policy"},
                                 {"searchpatterns", std::invoke([]() -> QJsonArray { return {}; })},
                                 {"url", "qrc:/qml/privatelicense.qml"}});
                   return array;
                   return array;
               })}});
            return array;
        })}});
}
