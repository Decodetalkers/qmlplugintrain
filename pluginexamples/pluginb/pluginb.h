#pragma once

#include <pluginInterface.h>

class PluginB final : public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_id)
    Q_INTERFACES(PluginInterface)
public:
    explicit PluginB();
    ~PluginB() = default;

    QString pluginName() const override;
    Interfaces::BaseModule *topModule() const override;
};
