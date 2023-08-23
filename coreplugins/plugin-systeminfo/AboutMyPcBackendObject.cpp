#include "AboutMyPcBackendObject.h"

#include <DSysInfo>

#include <QDir>
#include <QGuiApplication>

#include <math.h>

const QString HOSTNAME_SERVICE   = QStringLiteral("org.freedesktop.hostname1");
const QString HOSTNAME_PATH      = QStringLiteral("/org/freedesktop/hostname1");
const QString HOSTNAME_INTERFACE = QStringLiteral("org.freedesktop.hostname1");

const QString PLATFORM_NAME = std::visit([]() -> QString {
    QString platformname = QGuiApplication::platformName();
    if (platformname.contains("xcb")) {
        platformname = "x11";
    }
    return platformname;
});

// if there is lid, it is laptop
inline static bool
islaptopFileExist()
{
    return QDir("/proc/acpi/button/lid").exists();
}

static QString
formatCap(qulonglong cap, const int size = 1024, quint8 precision = 1)
{
    static QStringList type = {" B", " KB", " MB", " GB", " TB"};
    qulonglong lc           = cap;
    double dc               = cap;
    double ds               = size;

    for (int p = 0; p < type.count(); ++p) {
        if (cap < pow(size, p + 1) || p == type.count() - 1) {
            if (!precision) {
#ifdef __sw_64__
                return QString::number(ceil(lc / pow(size, p))) + type[p];
#else
                return QString::number(round(lc / pow(size, p))) + type[p];
#endif
            }

            return QString::number(dc / pow(ds, p), 'f', precision) + type[p];
        }
    }

    return "";
}

AboutMyPcBackendObject::AboutMyPcBackendObject(QObject *parent)
  : QObject(parent)
  , m_isLaptop(islaptopFileExist())
  , m_edition(std::nullopt)
  , m_cputype(std::nullopt)
  , m_processor(std::nullopt)
  , m_memory(std::nullopt)
  , m_graphicsPlatform(PLATFORM_NAME)
  , m_kernel(std::nullopt)
  , m_hostname1Inter(new DDBusInterface(HOSTNAME_SERVICE,
                                        HOSTNAME_PATH,
                                        HOSTNAME_INTERFACE,
                                        QDBusConnection::systemBus(),
                                        this))
{
    connectToDBus();
}

void
AboutMyPcBackendObject::connectToDBus()
{
    // NOTE: the signal by DDBusInterface cannot use directorly in qml, because in qml, you need set
    // once, then notify So, you should handle it again
    connect(
      this, &AboutMyPcBackendObject::StaticHostnameChanged, this, [this](const QString &value) {
          m_staticHostName = value;
          Q_EMIT staticHostnameChanged();
      });
}

void
AboutMyPcBackendObject::setStaticHostname(const QString &value)
{
    if (value == m_staticHostName) {
        return;
    }
    QList<QVariant> argumentList;
    argumentList << QVariant::fromValue(value) << QVariant::fromValue(true);
    m_hostname1Inter->asyncCallWithArgumentList("SetStaticHostname", argumentList);
}

using Dtk::Core::DSysInfo;

void
AboutMyPcBackendObject::active()
{
    m_staticHostName = qvariant_cast<QString>(m_hostname1Inter->property("StaticHostname"));
    Q_EMIT staticHostnameChanged();

    if (m_edition.has_value()) {
        return;
    }

    m_copyright = std::invoke([]() -> QString {
        bool useDeepinCopyRight = DSysInfo::productType() != DSysInfo::ProductType::Uos;
        if (useDeepinCopyRight) {
            return tr("Copyright© 2011-2023 Deepin Community");
        } else {
            return tr("Copyright© 2019-2023 UnionTech Software Technology Co., LTD");
        }
    });

    m_logo =
      QUrl::fromLocalFile(DSysInfo::distributionOrgLogo(DSysInfo::Distribution, DSysInfo::Normal));
    m_edition   = std::visit([]() -> QString {
        QString version;
        if (DSysInfo::uosType() == DSysInfo::UosServer ||
            DSysInfo::uosEditionType() == DSysInfo::UosEuler) {
            version = QString("%1%2").arg(DSysInfo::minorVersion(), DSysInfo::uosEditionName());
        } else if (DSysInfo::isDeepin()) {
            version = QString("%1 (%2)").arg(DSysInfo::uosEditionName(), DSysInfo::minorVersion());
        } else {
            version =
              QString("%1 %2").arg(DSysInfo::productVersion(), DSysInfo::productTypeString());
        }
        return version;
    });
    m_cputype   = QString("%1-bit").arg(QSysInfo::WordSize);
    m_kernel    = QSysInfo::kernelVersion();
    m_processor = DSysInfo::cpuModelName();
    m_memory    = std::visit([]() -> QString {
        qulonglong memoryTotalSize = static_cast<qulonglong>(DSysInfo::memoryTotalSize());
        QString mem                = formatCap(memoryTotalSize);
        return QString("%1 (%2)").arg(mem).arg(tr("available"));
    });
    Q_EMIT baseInformationChanged();
}
