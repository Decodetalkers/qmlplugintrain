#pragma once

#include <modulemodel.h>

#include <QObject>
#include <QUrl>

class PluginLoader final : public QObject
{
    Q_OBJECT
public:
    explicit PluginLoader(QObject *parent = nullptr);

    Q_PROPERTY(QList<Interfaces::BaseModule *> modules READ modules NOTIFY modulesChanged)
    inline QList<Interfaces::BaseModule *> modules() { return m_modules; }

signals:
    void modulesChanged();

private:
    void load_plugins();

private:
    QList<Interfaces::BaseModule *> m_modules;
};
