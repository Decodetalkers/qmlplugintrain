#include "dccPlugin.h"
#include "modulemodel.h"
#include <QtQml/QtQml>
#include <string_view>

void
DccPlugin::registerTypes(const char *uri)
{
    qmlRegisterUncreatableType<Interfaces::BaseModule>(uri, 1, 0, "ModuleModel", "Do it in Cpp");
    qmlRegisterUncreatableType<Interfaces::BaseModuleModel>(
      uri, 1, 0, "ModuleModelBase", "Do it in Cpp");
    qmlRegisterUncreatableType<Interfaces::HModuleModel>(uri, 1, 0, "HModuleModel", "Do it in Cpp");
    qmlRegisterUncreatableType<Interfaces::VModuleModel>(uri, 1, 0, "VModuleModel", "Do it in Cpp");
}
