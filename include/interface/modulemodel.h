#pragma once

#include <QAbstractListModel>
#include <QJsonObject>
#include <QObject>
#include <QUrl>

#include <optional>

namespace Interfaces {

struct SearchResult
{
    QString icon;
    QString display;
    QList<int> routine;
};

class BaseModuleModel;
class HModuleModel;
class VModuleModel;
class BaseModule;

int
insertModel(BaseModule *topModule, BaseModule *object, const QString &parentModule);

class BaseModule : public QAbstractListModel
{
    Q_OBJECT

public:
    static BaseModule *fromJson(QJsonObject object);
    virtual QString type() const                                             = 0;
    virtual QString displayName() const                                      = 0;
    virtual QString description() const                                      = 0;
    virtual QString icon() const                                             = 0;
    virtual int insertModel(BaseModule *object, const QString &parentModule) = 0;
    virtual bool isNotify() const                                            = 0;
    virtual bool isSpecial() const                                           = 0;
    virtual std::optional<QString> upModule()                                = 0;
    virtual QList<SearchResult> getAllRoutine()                              = 0;

public slots:
    virtual void setNotify(bool notify) = 0;

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
                             const QString &icon,
                             QStringList searchpatterns,
                             std::optional<QString> upModule,
                             const QUrl &url,
                             bool isSpecial,
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

    Q_PROPERTY(bool isNotify READ isNotify WRITE setNotify NOTIFY isNotifyChanged)
    bool isNotify() const override { return m_isNotify; }

    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)
    inline QString icon() const override { return m_icon; }

    Q_PROPERTY(bool isSpecial READ isSpecial NOTIFY isSpecialChanged)
    inline bool isSpecial() const override { return m_isSpecial; }

    int insertModel(BaseModule *object, const QString &parentModule) override { return -1; };

    inline std::optional<QString> upModule() override { return m_upModule; }

    QList<SearchResult> getAllRoutine() override { return {{m_icon, m_displayName, {}}}; }

    Q_INVOKABLE void appendPattern(const QString &pattern);

    Q_INVOKABLE void cleanPattern();

public slots:
    void setNotify(bool notify) override;

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
    void isNotifyChanged(bool);
    void iconChanged();
    void isSpecialChanged();

private:
    QString m_name;
    QString m_displayName;
    QString m_icon;
    QString m_description;
    QStringList m_searchpatterns;
    std::optional<QString> m_upModule;
    QUrl m_url;
    bool m_isSpecial;
    bool m_isNotify = false;
};

class HModuleModel final : public BaseModule
{
    Q_OBJECT

public:
    explicit HModuleModel(const QString &name,
                          const QString &displayName,
                          const QString &icon,
                          std::optional<QString> description,
                          QList<BaseModule *> models,
                          std::optional<QString> upModule,
                          bool isSpecial,
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
    QString description() const override;

    Q_PROPERTY(QList<BaseModule *> models READ models NOTIFY modelsChanged)
    inline QList<BaseModule *> models() const { return m_models; }

    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    inline QString type() const override { return "hmodule"; }

    Q_PROPERTY(bool isNotify READ isNotify WRITE setNotify NOTIFY isNotifyChanged)
    bool isNotify() const override { return m_isNotify; }

    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)
    inline QString icon() const override { return m_icon; }

    Q_PROPERTY(bool isSpecial READ isSpecial NOTIFY isSpecialChanged)
    inline bool isSpecial() const override { return m_isSpecial; }

    inline std::optional<QString> upModule() override { return m_upModule; }

    int insertModel(BaseModule *object, const QString &parentModule) override;
    QList<SearchResult> getAllRoutine() override;

public slots:
    void setNotify(bool notify) override;

private:
    QVariant getModelData(int row, int role) const;

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
    void isNotifyChanged(bool);
    void iconChanged();
    void isSpecialChanged();

private:
    QString m_name;
    QString m_displayName;
    QString m_icon;
    std::optional<QString> m_description;
    QList<BaseModule *> m_models;
    std::optional<QString> m_upModule;
    bool m_isSpecial;
    bool m_isNotify = false;
};

class VModuleModel final : public BaseModule
{
    Q_OBJECT

public:
    explicit VModuleModel(const QString &name,
                          const QString &displayName,
                          const QString &icon,
                          std::optional<QString> description,
                          QList<BaseModule *> models,
                          std::optional<QString> upModule,
                          bool isSpecial,
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
    QString description() const override;

    Q_PROPERTY(QList<BaseModule *> models READ models NOTIFY modelsChanged)
    inline QList<BaseModule *> models() const { return m_models; }

    Q_PROPERTY(QString type READ type NOTIFY typeChanged)
    inline QString type() const override { return "vmodule"; }

    Q_PROPERTY(bool isNotify READ isNotify WRITE setNotify NOTIFY isNotifyChanged)
    bool isNotify() const override { return m_isNotify; }

    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)
    inline QString icon() const override { return m_icon; }

    Q_PROPERTY(bool isSpecial READ isSpecial NOTIFY isSpecialChanged)
    inline bool isSpecial() const override { return m_isSpecial; }

    inline std::optional<QString> upModule() override { return m_upModule; }

    int insertModel(BaseModule *object, const QString &parentModule) override;
    QList<SearchResult> getAllRoutine() override;

private:
    QVariant getModelData(int row, int role) const;

private:
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void setNotify(bool notify) override;

signals:
    void nameChanged();
    void displayNameChanged();
    void descriptionChanged();
    void modelsChanged();
    void typeChanged();
    void isNotifyChanged(bool);
    void iconChanged();
    void isSpecialChanged();

private:
    QString m_name;
    QString m_displayName;
    QString m_icon;
    std::optional<QString> m_description;
    QList<BaseModule *> m_models;
    std::optional<QString> m_upModule;
    bool m_isSpecial;
    bool m_isNotify = false;
};
QDebug
operator<<(QDebug d, const BaseModule *model);
QDebug
operator<<(QDebug d, const BaseModuleModel *model);
QDebug
operator<<(QDebug d, const HModuleModel *model);
QDebug
operator<<(QDebug d, const VModuleModel *model);
QDebug
operator<<(QDebug d, const SearchResult &result);
}
