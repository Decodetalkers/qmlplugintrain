#include <modulemodel.h>

template<class... Ts>

struct overloaded : Ts...
{
    using Ts::operator()...;
};

// NOTE: in cpp 20, noneeded again
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

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
                           QList<ModuleModel> models,
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
    return get_model_data(index.row(), role);
}

QVariant
HModuleModel::get_model_data(int row, int role) const
{
    const ModuleModel data = m_models[row];
    return std::visit(overloaded{[role](BaseModuleModel *model) -> QVariant {
                                     switch (role) {
                                     case DisplayName:
                                         return model->displayName();
                                     case Description:
                                         return model->description();
                                     }
                                     return QVariant();
                                 },
                                 [role](HModuleModel *model) -> QVariant {
                                     switch (role) {
                                     case DisplayName:
                                         return model->displayName();
                                     case Description:
                                         return model->description();
                                     }
                                     return QVariant();
                                 },
                                 [role](VModuleModel *model) -> QVariant {
                                     switch (role) {
                                     case DisplayName:
                                         return model->displayName();
                                     case Description:
                                         return model->description();
                                     }
                                     return QVariant();
                                 }},
                      data);
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
                           QList<ModuleModel> models,
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
    return get_model_data(index.row(), role);
}

QVariant
VModuleModel::get_model_data(int row, int role) const
{
    const ModuleModel data = m_models[row];
    return std::visit(overloaded{[role](BaseModuleModel *model) -> QVariant {
                                     switch (role) {
                                     case DisplayName:
                                         return model->displayName();
                                     case Description:
                                         return model->description();
                                     }
                                     return QVariant();
                                 },
                                 [role](HModuleModel *model) -> QVariant {
                                     switch (role) {
                                     case DisplayName:
                                         return model->displayName();
                                     case Description:
                                         return model->description();
                                     }
                                     return QVariant();
                                 },
                                 [role](VModuleModel *model) -> QVariant {
                                     switch (role) {
                                     case DisplayName:
                                         return model->displayName();
                                     case Description:
                                         return model->description();
                                     }
                                     return QVariant();
                                 }},
                      data);
}

QHash<int, QByteArray>
VModuleModel::roleNames() const
{
    static const QHash<int, QByteArray> roles{{DisplayName, "displayName"},
                                              {Description, "description"}};
    return roles;
}
