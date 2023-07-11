import PluginA.Global
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
ColumnLayout {
    anchors.horizontalCenter: parent.horizontalCenter
    Text {
        Layout.alignment: Qt.AlignHCenter
        text: GlobalConst.name
    }
    Text {
        Layout.alignment: Qt.AlignHCenter
        text: GlobalConst.name
    }
}
