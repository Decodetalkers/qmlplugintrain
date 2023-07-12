#include <QJsonArray>

#include <functional>
#include <modulemodel.h>

#define FAILED -1
#define SUCCESSED 0

namespace Interfaces {

BaseModule::BaseModule(QObject *parent)
{
}

BaseModule *
BaseModule::fromJson(QJsonObject object)
{
    if (object["objectName"].toString() == "hmodule") {
        return new HModuleModel(
          object["name"].toString(),
          object["displayName"].toString(),
          object["icon"].isNull() ? "" : object["icon"].toString(),
          object["description"].isNull() ? std::nullopt
                                         : std::make_optional(object["description"].toString()),
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
          object["upModule"].isNull() ? std::make_optional(object["upModule"].toString())
                                      : std::nullopt);
    } else if (object["objectName"].toString() == "vmodule") {
        return new VModuleModel(
          object["name"].toString(),
          object["displayName"].toString(),
          object["icon"].isNull() ? "" : object["icon"].toString(),
          object["description"].isNull() ? std::nullopt
                                         : std::make_optional(object["description"].toString()),
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
          object["upModule"].isNull() ? std::make_optional(object["upModule"].toString())
                                      : std::nullopt);
    } else {
        return new BaseModuleModel(object["name"].toString(),
                                   object["displayName"].toString(),
                                   object["description"].toString(),
                                   object["icon"].isNull() ? "" : object["icon"].toString(),
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
                                 const QString &icon,
                                 QStringList searchpatterns,
                                 std::optional<QString> upModule,
                                 const QUrl &url,
                                 QObject *parent)
  : BaseModule(parent)
  , m_name(name)
  , m_displayName(displayName)
  , m_description(description)
  , m_icon(icon)
  , m_searchpatterns(searchpatterns)
  , m_upModule(upModule)
  , m_url(url)
{
}

void
BaseModuleModel::setNotify(bool notify)
{
    m_isNotify = notify;
    Q_EMIT isNotifyChanged(m_isNotify);
}

HModuleModel::HModuleModel(const QString &name,
                           const QString &displayName,
                           const QString &icon,
                           std::optional<QString> description,
                           QList<BaseModule *> models,
                           std::optional<QString> upModule,
                           QObject *parent)
  : BaseModule(parent)
  , m_name(name)
  , m_displayName(displayName)
  , m_description(description)
  , m_icon(icon)
  , m_models(models)
  , m_upModule(upModule)
{
    for (auto model : m_models) {
        if (model->type() == "base") {
            auto modelnew = dynamic_cast<BaseModuleModel *>(model);
            connect(modelnew, &BaseModuleModel::isNotifyChanged, this, &HModuleModel::setNotify);
        } else if (model->type() == "hmodule") {
            auto modelnew = dynamic_cast<HModuleModel *>(model);
            connect(modelnew, &HModuleModel::isNotifyChanged, this, &HModuleModel::setNotify);
        } else if (model->type() == "vmodule") {
            auto modelnew = dynamic_cast<VModuleModel *>(model);
            connect(modelnew, &VModuleModel::isNotifyChanged, this, &HModuleModel::setNotify);
        }
    }

    setNotify(true);
}

QString
HModuleModel::description() const
{
    if (m_description.has_value()) {
        return m_description.value();
    }
    QString description;
    for (const auto &model : m_models) {
        description.push_back(model->displayName());
        description.push_back(", ");
    }
    description.chop(2);
    return description;
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
        if (!m_description.has_value()) {
            setNotify(true);
            Q_EMIT descriptionChanged();
        }
        return SUCCESSED;
    }
    for (auto model : models()) {
        if (Interfaces::insert_model(model, object, parentModule) == 0) {
            setNotify(true);
            return SUCCESSED;
        }
    }
    return FAILED;
}

void
HModuleModel::setNotify([[maybe_unused]] bool notify)
{
    for (auto model : m_models) {
        if (model->isNotify()) {
            m_isNotify = true;
            Q_EMIT isNotifyChanged(m_isNotify);
            return;
        }
    }
    m_isNotify = false;
    Q_EMIT isNotifyChanged(m_isNotify);
}

VModuleModel::VModuleModel(const QString &name,
                           const QString &displayName,
                           const QString &icon,
                           std::optional<QString> description,
                           QList<BaseModule *> models,
                           std::optional<QString> upModule,
                           QObject *parent)
  : BaseModule(parent)
  , m_name(name)
  , m_displayName(displayName)
  , m_description(description)
  , m_icon(icon)
  , m_models(models)
  , m_upModule(upModule)
{
    for (auto model : m_models) {
        if (model->type() == "base") {
            auto modelnew = dynamic_cast<BaseModuleModel *>(model);
            connect(modelnew, &BaseModuleModel::isNotifyChanged, this, &VModuleModel::setNotify);
        } else if (model->type() == "hmodule") {
            auto modelnew = dynamic_cast<HModuleModel *>(model);
            connect(modelnew, &HModuleModel::isNotifyChanged, this, &VModuleModel::setNotify);
        } else if (model->type() == "vmodule") {
            auto modelnew = dynamic_cast<VModuleModel *>(model);
            connect(modelnew, &VModuleModel::isNotifyChanged, this, &VModuleModel::setNotify);
        }
    }
    setNotify(true);
}

QString
VModuleModel::description() const
{
    if (m_description.has_value()) {
        return m_description.value();
    }
    QString description;
    for (const auto &model : m_models) {
        description.push_back(model->displayName());
        description.push_back(", ");
    }
    description.chop(2);
    return description;
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
        if (!m_description.has_value()) {
            setNotify(true);
            Q_EMIT descriptionChanged();
        }
        return SUCCESSED;
    }
    for (auto model : models()) {
        if (Interfaces::insert_model(model, object, parentModule) == SUCCESSED) {
            setNotify(true);
            return SUCCESSED;
        }
    }
    return FAILED;
}

void
VModuleModel::setNotify([[maybe_unused]] bool notify)
{
    for (auto model : m_models) {
        if (model->isNotify()) {
            m_isNotify = true;
            Q_EMIT isNotifyChanged(m_isNotify);
            return;
        }
    }
    m_isNotify = false;
    Q_EMIT isNotifyChanged(m_isNotify);
}

QDebug
operator<<(QDebug d, const BaseModule *model)
{
    if (model->type() == "base") {
        d << dynamic_cast<const BaseModuleModel *>(model);
    } else if (model->type() == "hmodule") {
        d << dynamic_cast<const HModuleModel *>(model);
    } else if (model->type() == "vmodule") {
        d << dynamic_cast<const VModuleModel *>(model);
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
