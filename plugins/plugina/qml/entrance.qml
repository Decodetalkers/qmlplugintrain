import PluginA.Global
import QtQuick 2.15
import QtQuick.Layouts 1.11

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
