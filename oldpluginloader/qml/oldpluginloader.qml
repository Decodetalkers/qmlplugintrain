import Marine.Control 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

import OldPluginLoader 1.0

Page {
    property ModuleModelBase rootModel
    Rectangle {
        anchors.fill: parent
        Text {
            id: text
            anchors.margins: 20
            text: "This text is created with QML, the item below is a QWidget:"
        }
        OldPluginLoader {
            anchors.top: text.bottom
            anchors.topMargin: 15
            width: parent.width
            height: parent.height - text.height
        }
    }

}
