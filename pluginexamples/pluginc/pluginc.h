#pragma once

#include <pluginInterface.h>

class PluginC final : public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_id)
    Q_INTERFACES(PluginInterface)
public:
    explicit PluginC();
    ~PluginC() = default;

    QString pluginName() const override;
    Interfaces::BaseModule *topModule() const override;
    std::optional<u_int> position() const override { return 1; }
};
