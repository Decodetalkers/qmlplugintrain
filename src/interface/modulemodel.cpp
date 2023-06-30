#include <modulemodel.h>
#include <type_traits>

BaseModuleModel::BaseModuleModel(const QString &displayName,
                                 const QString &description,
                                 QStringList searchpatterns,
                                 std::optional<QString> upModule,
                                 const QUrl &url,
                                 QObject *parent)
  : QObject(parent)
  , m_displayName(displayName)
  , m_description(description)
  , m_searchpatterns(searchpatterns)
  , m_upModule(upModule)
  , m_url(url)
{
}
HModuleModel::HModuleModel(const QString &displayName,
                           const QString &description,
                           QList<ModuleModel *> models,
                           std::optional<QString> upModule,
                           QObject *parent)
  : QAbstractListModel(parent)
  , m_displayName(displayName)
  , m_description(description)
  , m_models(models)
  , m_upModule(upModule)
{
}

int
HModuleModel::rowCount(const QModelIndex &index) const
{
    return m_models.count();
}

QVariant
HModuleModel::data(const QModelIndex &index, int role) const
{
    if (role == DisplayName) {
        return m_displayName;
    }
    if (role == Description) {
        return m_description;
    }
    return QVariant();
}

QHash<int, QByteArray>
HModuleModel::roleNames() const
{
    static const QHash<int, QByteArray> roles{{DisplayName, "displayName"},
                                              {Description, "description"}};
    return roles;
}

VModuleModel::VModuleModel(const QString &displayName,
                           const QString &description,
                           QList<ModuleModel *> models,
                           std::optional<QString> upModule,
                           QObject *parent)
  : QAbstractListModel(parent)
  , m_displayName(displayName)
  , m_description(description)
  , m_models(models)
  , m_upModule(upModule)
{
}

int
VModuleModel::rowCount(const QModelIndex &index) const
{
    return m_models.count();
}

QVariant
VModuleModel::data(const QModelIndex &index, int role) const
{
    if (role == DisplayName) {
        return m_displayName;
    }
    if (role == Description) {
        return m_description;
    }
    return QVariant();
}

QHash<int, QByteArray>
VModuleModel::roleNames() const
{
    static const QHash<int, QByteArray> roles{{DisplayName, "displayName"},
                                              {Description, "description"}};
    return roles;
}
