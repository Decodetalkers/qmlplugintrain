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
        DccClock {
            Layout.alignment : Qt.AlignHCenter
            shift: 8
        }
        Button {
            Layout.alignment : Qt.AlignHCenter
            text: "Let's test it"
            onClicked: {
                rootModel.isNotify = !rootModel.isNotify;
            }
        }
        Item {
            Layout.fillHeight: true
        }
    }

}
