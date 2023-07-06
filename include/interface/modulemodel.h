#pragma once

#include <QAbstractListModel>
#include <QJsonObject>
#include <QObject>
#include <QUrl>

#include <optional>
#include <variant>

namespace Interfaces {
class BaseModuleModel;
class HModuleModel;
class VModuleModel;
class BaseModule;

int
insert_model(BaseModule *topModule, BaseModule *object, const QString &parentModule);

class BaseModule : public QAbstractListModel
{
    Q_OBJECT

public:
    static BaseModule *fromJson(QJsonObject object);
    virtual QString type() const                                              = 0;
    virtual QString displayName() const                                       = 0;
    virtual QString description() const                                       = 0;
    virtual int insert_model(BaseModule *object, const QString &parentModule) = 0;

protected:
    BaseModule(QObject *parent = nullptr);
};

class BaseModuleModel final : public BaseModule
{
    Q_OBJECT
public:
    explicit BaseModuleModel(const QString &name,
                             const QString &displayName,
                             const QString &description,
                             QStringList searchpatterns,
                             std::optional<QString> upModule,
                             const QUrl &url,
                             QObject *parent = nullptr);
    Q_PROPERTY(QStringList searchpatterns READ searchpatterns NOTIFY searchpatternsChanged)
    inline QStringList searchpatterns() const { return m_searchpatterns; }

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    inline QString name() const { return m_name; }

    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
    inline QString displayName() const override { return m_displayName; }

    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    inline QString description() const override { return m_description; }

    Q_PROPERTY(QUrl url READ url NOTIFY urlChanged)
    inline QUrl url() const { return m_url; }

    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    inline QString type() const override { return "base"; }

    int insert_model(BaseModule *object, const QString &parentModule) override { return -1; };

    inline std::optional<QString> upModule() { return m_upModule; }

private:
    int rowCount(const QModelIndex & = QModelIndex()) const override { return 0; };
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        return m_displayName;
    };
    QHash<int, QByteArray> roleNames() const override { return {}; };

signals:
    void nameChanged();
    void searchpatternsChanged();
    void displayNameChanged();
    void urlChanged();
    void descriptionChanged();
    void typeChanged();

private:
    QString m_name;
    QString m_displayName;
    QString m_description;
    QStringList m_searchpatterns;
    std::optional<QString> m_upModule;
    QUrl m_url;
};

class HModuleModel final : public BaseModule
{
    Q_OBJECT

public:
    explicit HModuleModel(const QString &name,
                          const QString &displayName,
                          const QString &description,
                          QList<BaseModule *> models,
                          std::optional<QString> upModule,
                          QObject *parent = nullptr);
    enum ModuleRole
    {
        DisplayName = Qt::DisplayRole,
        Description = Qt::UserRole,
    };
    Q_ENUM(ModuleRole)

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    inline QString name() const { return m_name; }

    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
    inline QString displayName() const override { return m_displayName; }

    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    inline QString description() const override { return m_description; }

    Q_PROPERTY(QList<BaseModule *> models READ models NOTIFY modelsChanged)
    inline QList<BaseModule *> models() const { return m_models; }

    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    inline QString type() const override { return "hmodule"; }

    inline std::optional<QString> upModule() { return m_upModule; }

    int insert_model(BaseModule *object, const QString &parentModule) override;

private:
    QVariant get_model_data(int row, int role) const;

private:
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void nameChanged();
    void displayNameChanged();
    void descriptionChanged();
    void modelsChanged();
    void typeChanged();

private:
    QString m_name;
    QString m_displayName;
    QString m_description;
    QList<BaseModule *> m_models;
    std::optional<QString> m_upModule;
};

class VModuleModel final : public BaseModule
{
    Q_OBJECT

public:
    explicit VModuleModel(const QString &name,
                          const QString &displayName,
                          const QString &description,
                          QList<BaseModule *> models,
                          std::optional<QString> upModule,
                          QObject *parent = nullptr);
    enum ModuleRole
    {
        DisplayName = Qt::DisplayRole,
        Description = Qt::UserRole,
    };
    Q_ENUM(ModuleRole)

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    inline QString name() const { return m_name; }

    Q_PROPERTY(QString displayName READ displayName NOTIFY displayNameChanged)
    inline QString displayName() const override { return m_displayName; }

    Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)
    inline QString description() const override { return m_description; }

    Q_PROPERTY(QList<BaseModule *> models READ models NOTIFY modelsChanged)
    inline QList<BaseModule *> models() const { return m_models; }

    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    inline QString type() const override { return "vmodule"; }

    inline std::optional<QString> upModule() { return m_upModule; }

    int insert_model(BaseModule *object, const QString &parentModule) override;

private:
    QVariant get_model_data(int row, int role) const;

private:
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void nameChanged();
    void displayNameChanged();
    void descriptionChanged();
    void modelsChanged();
    void typeChanged();

private:
    QString m_name;
    QString m_displayName;
    QString m_description;
    QList<BaseModule *> m_models;
    std::optional<QString> m_upModule;
};

QDebug
operator<<(QDebug d, const BaseModuleModel *model);
QDebug
operator<<(QDebug d, const HModuleModel *model);
QDebug
operator<<(QDebug d, const VModuleModel *model);

}
