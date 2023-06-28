#include "plugina.h"
#include <QUrl>
QString
PluginA::pluginName() const
{
    return "PluginA";
}

QUrl
PluginA::mainLink() const
{
    return QUrl("Todo!");
}
