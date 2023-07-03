#pragma once

#include <QObject>
#include <modulemodel.h>

class PluginInterface : public QObject
{
public:
    virtual QString pluginName() const    = 0;
    virtual QUrl mainLink() const         = 0;
    virtual Interfaces::ModuleModel topModule() const = 0;
};

#define PluginInterface_id "PLUGININTERFACE"

Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_id)
