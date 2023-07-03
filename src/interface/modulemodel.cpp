#include <QJsonArray>

#include <functional>
#include <modulemodel.h>
#include <qdatetime.h>
template<class... Ts>

struct overloaded : Ts...
{
    using Ts::operator()...;
};

// NOTE: in cpp 20, noneeded again
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
namespace Interfaces {

ModuleModel
model_fromjson(QJsonObject object)
{
    if (object["objectName"].toString() == "hmodule") {
        return new HModuleModel(object["name"].toString(),
                                object["displayName"].toString(),
                                object["description"].toString(),
                                std::invoke([object]() -> QList<ModuleModel> {
                                    if (object["models"].isNull()) {
                                        return {};
                                    }
                                    QList<ModuleModel> arrays;
                                    auto models = object["models"].toArray();
                                    for (auto arr : models) {
                                        QJsonObject model = arr.toObject();
                                        arrays.push_back(model_fromjson(model));
                                    }
                                    return arrays;
                                }),
                                object["upModule"].isNull()
                                  ? std::make_optional(object["upModule"].toString())
                                  : std::nullopt);
    } else if (object["objectName"].toString() == "vmodule") {
        return new VModuleModel(object["name"].toString(),
                                object["displayName"].toString(),
                                object["description"].toString(),
                                std::invoke([object]() -> QList<ModuleModel> {
                                    if (object["models"].isNull()) {
                                        return {};
                                    }
                                    QList<ModuleModel> arrays;
                                    auto models = object["models"].toArray();
                                    for (auto arr : models) {
                                        QJsonObject model = arr.toObject();
                                        arrays.push_back(model_fromjson(model));
                                    }
                                    return arrays;
                                }),
                                object["upModule"].isNull()
                                  ? std::make_optional(object["upModule"].toString())
                                  : std::nullopt);
    } else {
        return new BaseModuleModel(object["name"].toString(),
                                   object["displayName"].toString(),
                                   object["description"].toString(),
                                   std::invoke([object]() -> QStringList {
                                       if (object["searchpatterns"].isNull()) {
                                           return {};
                                       }

                                       QStringList arrays;
                                       auto patterns = object["searchpatterns"].toArray();
                                       for (auto pattern : patterns) {
                                           QString patt = pattern.toString();
                                           arrays.push_back(patt);
                                       }
                                       return arrays;
                                   }),
                                   object["upModule"].isNull()
                                     ? std::make_optional(object["upModule"].toString())
                                     : std::nullopt,
                                   object["url"].toString());
    }
}
int
insert_model(const ModuleModel &topModule, ModuleModel object, const QString &parentModule)
{
    return std::visit(overloaded{[](BaseModuleModel *model) -> int { return -1; },
                                 [object, parentModule](HModuleModel *model) -> int {
                                     return model->insert_model(object, parentModule);
                                 },
                                 [object, parentModule](VModuleModel *model) -> int {
                                     return model->insert_model(object, parentModule);
                                 }},
                      topModule);
};
BaseModuleModel::BaseModuleModel(const QString &name,
                                 const QString &displayName,
                                 const QString &description,
                                 QStringList searchpatterns,
                                 std::optional<QString> upModule,
                                 const QUrl &url,
                                 QObject *parent)
  : QObject(parent)
  , m_name(name)
  , m_displayName(displayName)
  , m_description(description)
  , m_searchpatterns(searchpatterns)
  , m_upModule(upModule)
  , m_url(url)
{
}

HModuleModel::HModuleModel(const QString &name,
                           const QString &displayName,
                           const QString &description,
                           QList<ModuleModel> models,
                           std::optional<QString> upModule,
                           QObject *parent)
  : QAbstractListModel(parent)
  , m_name(name)
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
                                     [[unlikely]] default:
                                         return QVariant();
                                     }
                                 },
                                 [role](HModuleModel *model) -> QVariant {
                                     switch (role) {
                                     case DisplayName:
                                         return model->displayName();
                                     case Description:
                                         return model->description();
                                     [[unlikely]] default:
                                         return QVariant();
                                     }
                                 },
                                 [role](VModuleModel *model) -> QVariant {
                                     switch (role) {
                                     case DisplayName:
                                         return model->displayName();
                                     case Description:
                                         return model->description();
                                     [[unlikely]] default:
                                         return QVariant();
                                     }
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

int
HModuleModel::insert_model(ModuleModel object, const QString &parentModule)
{
    if (parentModule == name()) {
        m_models.append(object);
        return 0;
    }
    for (auto model : models()) {
        if (Interfaces::insert_model(model, object, parentModule) == 0) {
            return 0;
        }
    }
    return -1;
}

VModuleModel::VModuleModel(const QString &name,
                           const QString &displayName,
                           const QString &description,
                           QList<ModuleModel> models,
                           std::optional<QString> upModule,
                           QObject *parent)
  : QAbstractListModel(parent)
  , m_name(name)
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
                                     [[unlikely]] default:
                                         return QVariant();
                                     }
                                 },
                                 [role](HModuleModel *model) -> QVariant {
                                     switch (role) {
                                     case DisplayName:
                                         return model->displayName();
                                     case Description:
                                         return model->description();
                                     [[unlikely]] default:
                                         return QVariant();
                                     }
                                 },
                                 [role](VModuleModel *model) -> QVariant {
                                     switch (role) {
                                     case DisplayName:
                                         return model->displayName();
                                     case Description:
                                         return model->description();
                                     [[unlikely]] default:
                                         return QVariant();
                                     }
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

int
VModuleModel::insert_model(ModuleModel object, const QString &parentModule)
{
    if (parentModule == name()) {
        m_models.append(object);
        return 0;
    }
    for (auto model : models()) {
        if (Interfaces::insert_model(model, object, parentModule) == 0) {
            return 0;
        }
    }
    return -1;
}

QDebug
operator<<(QDebug d, const ModuleModel &model)
{
    return std::visit(overloaded{[d](BaseModuleModel *model) -> QDebug {
                                     d << model;
                                     return d;
                                 },
                                 [d](HModuleModel *model) -> QDebug {
                                     d << model;
                                     return d;
                                 },
                                 [d](VModuleModel *model) -> QDebug {
                                     d << model;
                                     return d;
                                 }},
                      model);
}

QDebug
operator<<(QDebug d, const BaseModuleModel *model)
{
    d << "{"
      << "name: " << model->name() << ","
      << "displayName: " << model->displayName() << ","
      << "searchpatterns: " << model->searchpatterns() << "}";
    return d;
}
QDebug
operator<<(QDebug d, const HModuleModel *model)
{
    d << "{"
      << "name: " << model->name() << ","
      << "displayName: " << model->displayName() << ","
      << "models: " << model->models() << "}";
    return d;
}

QDebug
operator<<(QDebug d, const VModuleModel *model)
{
    d << "{"
      << "name: " << model->name() << ","
      << "displayName: " << model->displayName() << ","
      << "models: " << model->models() << "}";
    return d;
}
}
