#include <QJsonArray>

#include <functional>
#include <modulemodel.h>
#include <type_traits>

#define FAILED -1
#define SUCCESSED 0

template<class... Ts>

struct overloaded : Ts...
{
    using Ts::operator()...;
};

// NOTE: in cpp 20, noneeded again
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
namespace Interfaces {

BaseModule::BaseModule(QObject *parent)
{
}

BaseModule *
BaseModule::fromJson(QJsonObject object)
{
    if (object["objectName"].toString() == "hmodule") {
        return new HModuleModel(object["name"].toString(),
                                object["displayName"].toString(),
                                object["description"].toString(),
                                std::invoke([object]() -> QList<BaseModule *> {
                                    if (object["models"].isNull()) {
                                        return {};
                                    }
                                    QList<BaseModule *> arrays;
                                    auto models = object["models"].toArray();
                                    for (auto arr : models) {
                                        QJsonObject model = arr.toObject();
                                        arrays.push_back(fromJson(model));
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
                                std::invoke([object]() -> QList<BaseModule *> {
                                    if (object["models"].isNull()) {
                                        return {};
                                    }
                                    QList<BaseModule *> arrays;
                                    auto models = object["models"].toArray();
                                    for (auto arr : models) {
                                        QJsonObject model = arr.toObject();
                                        arrays.push_back(fromJson(model));
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
                                   QUrl(object["url"].toString()));
    }
}

int
insert_model(BaseModule *topModule, BaseModule *object, const QString &parentModule)
{
    return topModule->insert_model(object, parentModule);
};

BaseModuleModel::BaseModuleModel(const QString &name,
                                 const QString &displayName,
                                 const QString &description,
                                 QStringList searchpatterns,
                                 std::optional<QString> upModule,
                                 const QUrl &url,
                                 QObject *parent)
  : BaseModule(parent)
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
                           QList<BaseModule *> models,
                           std::optional<QString> upModule,
                           QObject *parent)
  : BaseModule(parent)
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
    const BaseModule *data = m_models[row];
    switch (role) {
    case DisplayName:
        return data->displayName();
    case Description:
        return data->description();
    [[unlikely]] default:
        return QVariant();
    }
}

QHash<int, QByteArray>
HModuleModel::roleNames() const
{
    static const QHash<int, QByteArray> roles{{DisplayName, "displayName"},
                                              {Description, "description"}};
    return roles;
}

int
HModuleModel::insert_model(BaseModule *object, const QString &parentModule)
{
    if (parentModule == name()) {
        m_models.append(object);
        return SUCCESSED;
    }
    for (auto model : models()) {
        if (Interfaces::insert_model(model, object, parentModule) == 0) {
            return SUCCESSED;
        }
    }
    return FAILED;
}

VModuleModel::VModuleModel(const QString &name,
                           const QString &displayName,
                           const QString &description,
                           QList<BaseModule *> models,
                           std::optional<QString> upModule,
                           QObject *parent)
  : BaseModule(parent)
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
    const BaseModule *data = m_models[row];
    switch (role) {
    case DisplayName:
        return data->displayName();
    case Description:
        return data->description();
    [[unlikely]] default:
        return QVariant();
    }
}

QHash<int, QByteArray>
VModuleModel::roleNames() const
{
    static const QHash<int, QByteArray> roles{{DisplayName, "displayName"},
                                              {Description, "description"}};
    return roles;
}

int
VModuleModel::insert_model(BaseModule *object, const QString &parentModule)
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
operator<<(QDebug d, const BaseModule *model)
{
    using T = std::decay_t<decltype(model)>;
    if constexpr (std::is_same_v<T, const BaseModuleModel *>) {
        d << dynamic_cast<const BaseModuleModel *>(model);
    } else if constexpr (std::is_same_v<T, const HModuleModel *>) {
        d << dynamic_cast<const HModuleModel *>(model);
    } else if constexpr (std::is_same_v<T, const VModuleModel *>) {
        d << dynamic_cast<const VModuleModel *>(model);
    } else {
        d << model;
    }
    return d;
}

QDebug
operator<<(QDebug d, const BaseModuleModel *model)
{
    d << "{"
      << "name: " << model->name() << ","
      << "displayName: " << model->displayName() << ","
      << "searchpatterns: " << model->searchpatterns() << ","
      << "url :" << model->url() << "}";
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
