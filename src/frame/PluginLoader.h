#pragma once

#include <modulemodel.h>

#include <QObject>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QUrl>

class PluginModel final : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PluginModel(QObject *parent = nullptr);
    enum RoutineRole
    {
        Display = Qt::DisplayRole,
        Routine,
    };
    Q_ENUM(RoutineRole)

    void clear();
    void insert(Interfaces::SearchResult &result);

private:
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Interfaces::SearchResult> m_results;
};

class PluginLoader final : public QObject
{
    Q_OBJECT
public:
    explicit PluginLoader(QObject *parent = nullptr);

    Q_PROPERTY(QList<Interfaces::BaseModule *> modules READ modules NOTIFY modulesChanged)
    inline QList<Interfaces::BaseModule *> modules() { return m_modules; }

    Q_PROPERTY(QAbstractItemModel *searchPattern READ searchPattern NOTIFY searchPatternChanged)
    inline QAbstractItemModel *searchPattern() { return m_proxyModel; }

    Q_INVOKABLE void getModel(const QString &pattern);

    enum RoutineRole
    {
        Display = Qt::DisplayRole,
        Routine,
    };
    Q_ENUM(RoutineRole)

signals:
    void modulesChanged();
    void searchPatternChanged();

private:
    void setProxy();
    void resetModel();
    QList<Interfaces::SearchResult> getAllRoutine();
    void loadPlugins();

private:
    QList<Interfaces::BaseModule *> m_modules;
    PluginModel *m_model;
    QSortFilterProxyModel *m_proxyModel;
};
