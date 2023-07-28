import Marine.Control 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

ScrollablePage {
    id: root
    property ModuleModelBase rootModel
    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            Layout.preferredHeight: 10
        }

        DccClock {
            Layout.alignment : Qt.AlignHCenter
            shift: 8
        }

        Item {
            Layout.preferredHeight: 5
        }

        SettingRowItem {
            Layout.alignment : Qt.AlignHCenter
            implicitWidth: root.width > 1500 ? 1400 : root.width - 100
            Label {
                text: qsTr("Auto Sync")
                Layout.fillWidth: true
                font.bold: true
            }
            Switch {
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }

}
