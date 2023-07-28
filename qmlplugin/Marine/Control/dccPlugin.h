#pragma once

#include <QtQml/QQmlExtensionPlugin>

class DccPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Marine.Control/1.0")

public:
    void registerTypes(const char *uri) override;
};
