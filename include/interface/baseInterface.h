#pragma once

#include <QObject>
#include <modulemodel.h>
#include <optional>
#include <sys/types.h>

class PluginInterface : public QObject
{
public:
    virtual QString pluginName() const                = 0;
    virtual Interfaces::BaseModule *topModule() const = 0;
    virtual std::optional<u_int> position() const { return std::nullopt; }
};

#define PluginInterface_id "PLUGININTERFACE"

Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_id)
