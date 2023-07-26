import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import QtQml 2.15

ScrollView {
    id: page
    property alias model: head.model
    property alias currentIndex: header.currentIndex

    clip: true
    Control {
        id: control
        width: page.width

        topPadding: 2
        bottomPadding: 2

        contentItem: RowLayout {
            id: header
            property int currentIndex : head.model.length == 0 ? -1 : 0

            Item {
                Layout.fillWidth : true
            }

            Repeater {
                id: head

                Button {
                    checkable: true
                    checked: index == header.currentIndex
                    onClicked : {
                        header.currentIndex = index
                    }
                    contentItem: RowLayout {
                        width: 10
                        anchors.fill: parent
                        Item {
                            Layout.preferredWidth: 10
                        }

                        Label {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            verticalAlignment: Qt.AlignVCenter
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                            text: modelData.displayName
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        RedDot {
                            visible: modelData.isNotify
                        }

                        Item {
                            Layout.preferredWidth: 10
                        }
                    }
                }

            }

            Item {
                Layout.fillWidth : true
            }

        }
    }
}

