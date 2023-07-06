#pragma once

#include <QObject>
class GlobalConst final : public QObject
{
    Q_OBJECT
public:
    explicit GlobalConst(QObject *parent = nullptr);

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    inline QString name() { return "abcd"; }

signals:

    void nameChanged();
};
