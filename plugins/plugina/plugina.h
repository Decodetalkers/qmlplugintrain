#pragma once

#include <baseInterface.h>

class PluginA : public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_id)
    Q_INTERFACES(PluginInterface)
public:
    PluginA(){};
    ~PluginA() = default;

    QString pluginName() const override;
    QUrl mainLink() const override;
};
