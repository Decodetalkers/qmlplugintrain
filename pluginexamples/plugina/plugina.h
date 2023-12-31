#pragma once

#include <pluginInterface.h>

class PluginA final: public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_id)
    Q_INTERFACES(PluginInterface)
public:
    explicit PluginA();
    ~PluginA() = default;

    QString pluginName() const override;
    Interfaces::BaseModule* topModule() const override;
};
