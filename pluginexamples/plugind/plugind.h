#pragma once

#include <baseInterface.h>

class PluginD final : public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_id)
    Q_INTERFACES(PluginInterface)
public:
    explicit PluginD();
    ~PluginD() = default;

    QString pluginName() const override;
    Interfaces::BaseModule *topModule() const override;
    std::optional<u_int> position() const override { return 0; }
};
