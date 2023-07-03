#pragma once

#include <optional>
#include <qurl.h>
#include <variant>

#include <QAbstractListModel>
#include <QObject>

class BaseModuleModel;
class HModuleModel;
class VModuleModel;
using ModuleModel = std::variant<BaseModuleModel *, HModuleModel *, VModuleModel *>;

class BaseModuleModel final : public QObject
{
    Q_OBJECT
public:
    explicit BaseModuleModel(const QString &displayName,
                             const QString &description,
                             QStringList searchpatterns,
                             std::optional<QString> upModule,
                             const QUrl &url,
                             QObject *parent = nullptr);
    Q_PROPERTY(QStringList searchpatterns READ searchpatterns NOTIFY searchpatternsChanged)
    inline QStringList searchpatterns() { return m_searchpatterns; }

    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
    inline QString displayName() const { return m_displayName; }

    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    inline QString description() const { return m_description; }

    Q_PROPERTY(QUrl url READ url NOTIFY urlChanged)
    inline QUrl url() const { return m_url; }

    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    inline QString type() { return "base"; }

    inline std::optional<QString> upModule() { return m_upModule; }

signals:
    void searchpatternsChanged();
    void displayNameChanged();
    void urlChanged();
    void descriptionChanged();
    void typeChanged();

private:
    QString m_displayName;
    QString m_description;
    QStringList m_searchpatterns;
    std::optional<QString> m_upModule;
    QUrl m_url;
};

class HModuleModel final : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit HModuleModel(const QString &displayName,
                          const QString &description,
                          QList<ModuleModel> models,
                          std::optional<QString> upModule,
                          QObject *parent = nullptr);
    enum ModuleRole
    {
        DisplayName = Qt::DisplayRole,
        Description = Qt::UserRole,
    };
    Q_ENUM(ModuleRole)

    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
    inline QString displayName() const { return m_displayName; }

    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    inline QString description() const { return m_description; }

    Q_PROPERTY(QList<ModuleModel> models READ models NOTIFY modelsChanged)
    inline QList<ModuleModel> models() { return m_models; }

    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    inline QString type() { return "hmodule"; }

    inline std::optional<QString> upModule() { return m_upModule; }

private:
    QVariant get_model_data(int row, int role) const;

private:
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void displayNameChanged();
    void descriptionChanged();
    void modelsChanged();
    void typeChanged();

private:
    QString m_displayName;
    QString m_description;
    QList<ModuleModel> m_models;
    std::optional<QString> m_upModule;
};

class VModuleModel final : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit VModuleModel(const QString &displayName,
                          const QString &description,
                          QList<ModuleModel> models,
                          std::optional<QString> upModule,
                          QObject *parent = nullptr);
    enum ModuleRole
    {
        DisplayName = Qt::DisplayRole,
        Description = Qt::UserRole,
        Model,
    };
    Q_ENUM(ModuleRole)

    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
    inline QString displayName() const { return m_displayName; }

    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    inline QString description() const { return m_description; }

    Q_PROPERTY(QList<ModuleModel> models READ models NOTIFY modelsChanged)
    inline QList<ModuleModel> models() { return m_models; }

    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    inline QString type() { return "vmodule"; }

    inline std::optional<QString> upModule() { return m_upModule; }

private:
    QVariant get_model_data(int row, int role) const;

private:
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void displayNameChanged();
    void descriptionChanged();
    void modelsChanged();
    void typeChanged();

private:
    QString m_displayName;
    QString m_description;
    QList<ModuleModel> m_models;
    std::optional<QString> m_upModule;
};
