import Marine.Control 1.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

import QtQuick 2.15

ScrollablePage {
    id: root

    property ModuleModelBase rootModel

    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        SettingGroup {
            Layout.alignment : Qt.AlignHCenter
            title: "Date"
            implicitWidth: root.width > 1500 ? 1400 : root.width - 100
            SettingRowLayout {
                Layout.alignment : Qt.AlignHCenter
                implicitWidth: root.width > 1500 ? 1400 : root.width - 100
                Label {
                    text: qsTr("Server")
                    Layout.fillWidth: true
                    font.bold: true
                }
                ComboBox {
                    editable: false
                    model: ListModel {
                        id: model
                        ListElement { text: "1.debian.pool.ntp.org" }
                        ListElement { text: "1.debian.pool.ntp.org" }
                        ListElement { text: "1.debian.pool.ntp.org" }
                        ListElement { text: "1.debian.pool.ntp.org" }
                        ListElement { text: "1.debian.pool.ntp.org" }
                    }
                }
            }
        }
    }
}
