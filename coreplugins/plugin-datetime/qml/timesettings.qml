import Marine.Control 1.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

import QtQuick 2.15

ScrollablePage {
    id: root

    property ModuleModelBase rootModel
    property int year
    property int month
    property int day
    property int hours
    property int minutes

    property int itemWidth: root.width > 1500 ? 1400 : root.width - 100

    Item {
        Timer {
            interval: 100; running: true; repeat: true;
            onTriggered: root.timeChanged()
        }
    }

    function timeChanged() {
        var date = new Date;
        year = date.getFullYear();
        month = date.getMonth() + 1;
        day = date.getDate();
        hours = date.getHours();
        minutes = date.getMinutes();
    }

    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            Layout.preferredHeight: 10
        }

        DccClock {
            Layout.alignment : Qt.AlignHCenter
        }

        Item {
            Layout.preferredHeight: 5
        }

        SettingRowLayout {
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
        SettingRowLayout {
            color: "transparent"
            Layout.alignment : Qt.AlignHCenter
            implicitWidth: root.width > 1500 ? 1400 : root.width - 100
            implicitHeight: 60
            Rectangle {
                color: "transparent"
                Layout.fillWidth: true
                implicitHeight: 60
                Label {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: root.hours
                    font.pointSize: 25
                    font.bold: true
                }
            }
            Rectangle {
                color: "transparent"
                Layout.fillWidth: true
                implicitHeight: 60
                Label {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: ":"
                    font.pointSize: 25
                    font.bold: true
                }
            }
            Rectangle {
                color: "transparent"
                Layout.fillWidth: true
                implicitHeight: 60

                Label {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 25
                    text: root.minutes
                    font.bold: true
                }
            }
        }

        SettingRowLayout{
            Layout.alignment : Qt.AlignHCenter
            implicitWidth: root.width > 1500 ? 1400 : root.width - 100
            Rectangle {
                color: "transparent"
                Layout.fillWidth: true
                height: 22
                Label {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    text: root.year + " " + qsTr("Year")
                    font.bold: true
                }
            }
            Rectangle {
                color: "transparent"
                Layout.fillWidth: true
                height: 22
                Label {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    text: root.month + " " + qsTr("Month")
                    font.bold: true
                }
            }
            Rectangle {
                color: "transparent"
                Layout.fillWidth: true
                height: 22
                Label {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    text: root.day + " " + qsTr("Day")
                    font.bold: true
                }
            }

        }

        Item {
            Layout.fillHeight: true
        }
    }

}
