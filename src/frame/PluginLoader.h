#pragma once

#include <modulemodel.h>

#include <QObject>
#include <QUrl>

class PluginLoader final : public QObject
{
    Q_OBJECT
public:
    explicit PluginLoader(QObject *parent = nullptr);

    Q_PROPERTY(QList<Interfaces::ModuleModel> modules READ modules NOTIFY modulesChanged)
    inline QList<Interfaces::ModuleModel> modules() { return m_modules; }

    Q_PROPERTY(QStringList names READ names NOTIFY namesChanged)
    inline QStringList names() { return {"aa", "bb", "cc"}; }
signals:
    void urlLoader(QUrl);
    void modulesChanged();
    void namesChanged();

private:
    void load_plugins();

private:
    QList<Interfaces::ModuleModel> m_modules;
};
