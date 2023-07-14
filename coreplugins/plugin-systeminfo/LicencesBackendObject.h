#pragma once

#include <QObject>

#include <optional>

class LicenseBackendObject final : public QObject
{
    Q_OBJECT
public:
    explicit LicenseBackendObject(QObject *parent = nullptr);

    Q_PROPERTY(QString gnuLicense READ gnuLicense NOTIFY gnuLicenseChanged)

    inline QString gnuLicense() { return m_gnuLicense.value_or(QString()); }

    Q_PROPERTY(QString gnuLicenseTitle READ gnuLicenseTitle NOTIFY gnuLicenseTitleChanged)

    inline QString gnuLicenseTitle() { return m_gnuLicenseTitle.value_or(QString()); }

    Q_PROPERTY(QString privateLicense READ privateLicense NOTIFY privateLicenseChanged)

    inline QString privateLicense() { return m_privateLicense; }

    Q_PROPERTY(QString privateLicenseTitle READ privateLicenseTitle NOTIFY privateLicenseTitleChanged)

    inline QString privateLicenseTitle() { return m_privateLicenseTitle; }

public slots:
    Q_INVOKABLE void active();

signals:
    void gnuLicenseChanged();
    void gnuLicenseTitleChanged();
    void privateLicenseChanged();
    void privateLicenseTitleChanged();

private:
    std::optional<QString> m_gnuLicense;
    std::optional<QString> m_gnuLicenseTitle;
    QString m_privateLicense;
    QString m_privateLicenseTitle;
};
