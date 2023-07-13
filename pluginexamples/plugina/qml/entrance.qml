import Marine.Model 1.0
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
        text: "test"
        onClicked: {
            console.log(rootModel.isNotify);
            rootModel.isNotify = !rootModel.isNotify;
        }
    }

}
