import Marine.Control 1.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

import QtQuick 2.15

ScrollablePage {
    id: root

    property ModuleModelBase rootModel

    ColumnLayout {
        spacing: 15
        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            Layout.preferredWidth: 5
        }
        SettingGroup {
            columnspacing: 5
            Layout.alignment : Qt.AlignHCenter
            title: "Time"
            implicitWidth: root.width > 1500 ? 1400 : root.width - 100
            SettingRowLayout {
                Layout.alignment : Qt.AlignHCenter
                Layout.fillWidth: true
                Label {
                    text: qsTr("24-hour Time")
                    Layout.fillWidth: true
                    font.bold: true
                }
                Switch {}
            }
            SettingRowLayout {
                Layout.alignment : Qt.AlignHCenter
                Layout.fillWidth: true
                Label {
                    text: qsTr("Short time")
                    Layout.fillWidth: true
                    font.bold: true
                }
                ComboBox {
                    editable: false
                    model: ListModel {
                        ListElement { text: qsTr("9:40") }
                        ListElement { text: qsTr("09:40")}
                    }
                }
            }
            SettingRowLayout {
                Layout.alignment : Qt.AlignHCenter
                Layout.fillWidth: true
                Label {
                    text: qsTr("Long time")
                    Layout.fillWidth: true
                    font.bold: true
                }
                ComboBox {
                    editable: false
                    model: ListModel {
                        ListElement { text: qsTr("9:40:07") }
                        ListElement { text: qsTr("09:40:07")}
                    }
                }
            }
        }
        SettingGroup {
            columnspacing: 5
            Layout.alignment : Qt.AlignHCenter
            title: "Date"
            implicitWidth: root.width > 1500 ? 1400 : root.width - 100
            SettingRowLayout {
                Layout.alignment : Qt.AlignHCenter
                Layout.fillWidth: true
                Label {
                    text: qsTr("First Day of Week")
                    Layout.fillWidth: true
                    font.bold: true
                }
                ComboBox {
                    editable: false
                    model: ListModel {
                        ListElement { text: qsTr("Monday") }
                        ListElement { text: qsTr("monday")}
                    }
                }
            }
            SettingRowLayout {
                Layout.alignment : Qt.AlignHCenter
                Layout.fillWidth: true
                Label {
                    text: qsTr("Short Date")
                    Layout.fillWidth: true
                    font.bold: true
                }
                ComboBox {
                    editable: false
                    model: ListModel {
                        ListElement { text: qsTr("2020/4/5") }
                        ListElement { text: qsTr("2020-4-5")}
                        ListElement { text: qsTr("2020.4.5")}
                        ListElement { text: qsTr("2020/04/05")}
                        ListElement { text: qsTr("2020-04-05")}
                        ListElement { text: qsTr("2020.04.05")}
                        ListElement { text: qsTr("20/4/5")}
                        ListElement { text: qsTr("20-4-5")}
                        ListElement { text: qsTr("20.4.5")}
                    }
                }
            }
            SettingRowLayout {
                Layout.alignment : Qt.AlignHCenter
                Layout.fillWidth: true
                Label {
                    text: qsTr("Long Date")
                    Layout.fillWidth: true
                    font.bold: true
                }
                ComboBox {
                    editable: false
                    model: ListModel {
                        ListElement { text: qsTr("April 5, 2020") }
                        ListElement { text: qsTr("April 5, 2020, Sunday")}
                        ListElement { text: qsTr("Sounday, April 5, 2020")}
                    }
                }
            }
        }
    }
}
