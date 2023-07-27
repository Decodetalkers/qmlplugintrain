import Marine.Control 1.0
import PluginB.Global 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Page {
    property ModuleModelBase rootModel

    ColumnLayout {
        anchors.fill: parent

        Item {
            Layout.fillHeight: true
        }

        Text {
            Layout.alignment : Qt.AlignHCenter
            text: GlobalConst.name
        }

        Button {
            Layout.alignment : Qt.AlignHCenter
            text: "Test it!!!"
            onClicked: {
                rootModel.isNotify = !rootModel.isNotify;
            }
        }

        Item {
            Layout.fillHeight: true
        }

    }

}
