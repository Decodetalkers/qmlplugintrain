#include "oldpluginloader.h"

#include <QPainter>
#include <QPushButton>

void
registerGlobalTypes()
{
    qmlRegisterType<WidgetItem>("OldPluginLoader", 1, 0, "OldPluginLoader");
}

static QPushButton *BACKEND = nullptr;

QPushButton *
get_pushbutton()
{
    if (BACKEND) {
        return BACKEND;
    }

    return new QPushButton("Abcd");
}

WidgetItem::WidgetItem(QQuickItem *parent)
  : QQuickPaintedItem(parent)
  , m_widget(get_pushbutton())
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
