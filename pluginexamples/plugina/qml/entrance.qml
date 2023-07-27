import Marine.Control 1.0
import PluginA.Global 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

ColumnLayout {
    property ModuleModelBase rootModel

    anchors.horizontalCenter: parent.horizontalCenter

    Text {
        Layout.alignment: Qt.AlignHCenter
        text: GlobalConst.name
    }

    Text {
        Layout.alignment: Qt.AlignHCenter
        text: GlobalConst.name
    }

    Button {
        Layout.alignment: Qt.AlignHCenter
        text: "Test it"
        onClicked: {
            rootModel.isNotify = !rootModel.isNotify;
        }
    }

}
