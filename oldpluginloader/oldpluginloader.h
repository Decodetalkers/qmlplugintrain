#pragma once

#include <QPointer>
#include <QPushButton>
#include <QQuickPaintedItem>
#include <QWidget>
#include <pluginInterface.h>

class WidgetItem : public QQuickPaintedItem
{
    Q_OBJECT

public:
    WidgetItem(QQuickItem *parent = nullptr);

    void setWidget(QWidget *widget);

    virtual void paint(QPainter *painter) override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPointer<QWidget> m_widget;
};

class OldPluginLoader final : public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterface_id)
    Q_INTERFACES(PluginInterface)
public:
    explicit OldPluginLoader();
    ~OldPluginLoader() = default;

    QString pluginName() const override;
    Interfaces::BaseModule *topModule() const override;
};
