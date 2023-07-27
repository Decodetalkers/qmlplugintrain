#include "oldpluginloader.h"

#include <QPainter>
#include <QPushButton>

void
registerGlobalTypes()
{
    qmlRegisterType<WidgetItem>("OldPluginLoader", 1, 0, "OldPluginLoader");
}

WidgetItem::WidgetItem(QQuickItem *parent)
  : QQuickPaintedItem(parent)
  , m_widget(new QPushButton("Abcd"))
{
    setAcceptTouchEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
}

void
WidgetItem::setWidget(QWidget *widget)
{
    m_widget = widget;
}

void
WidgetItem::paint(QPainter *painter)
{
    if (m_widget) {
        m_widget->render(painter);
    }
}

void
WidgetItem::mousePressEvent(QMouseEvent *event)
{
    if (m_widget) {
        QCoreApplication::sendEvent(m_widget, event);
        update();
    }
}

void
WidgetItem::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_widget) {
        QCoreApplication::sendEvent(m_widget, event);
        update();
    }
}

OldPluginLoader::OldPluginLoader()
{
    registerGlobalTypes();
}

QString
OldPluginLoader::pluginName() const
{
    return "OldPluginLoader";
}

Interfaces::BaseModule *
OldPluginLoader::topModule() const
{
    return Interfaces::BaseModule::fromJson(
      {{"objectName", "base"},
       {"name", "OldPluginLoader"},
       {"displayName", tr("OldPluginLoader")},
       {"icon", "gparted"},
       {"description", tr("OldPluginLoader")},
       {"url", "qrc:/oldpluginloader/qml/oldpluginloader.qml"}});
}
