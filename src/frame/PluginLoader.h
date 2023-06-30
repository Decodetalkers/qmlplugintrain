#pragma once

#include <QObject>
#include <QUrl>

class PluginLoader final : public QObject
{
    Q_OBJECT
public:
    explicit PluginLoader(QObject *parent = nullptr);
signals:
    void urlLoader(QUrl);
private:
    void load_plugins();
};
