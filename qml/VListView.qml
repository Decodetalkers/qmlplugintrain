import "."
import "components"

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1

import org.deepin.dtk 1.0 as Dtk

import QtQml 2.15

Row {
    id: page

    property alias model: leftview.model
    property alias pageHeight: page.height
    property alias pageWidth: page.width

    ListView {
        id: leftview

        height: parent.height
        width: leftview.currentIndex < 0 ? 0 : 270
        visible: leftview.currentIndex >= 0
        focus: true
        spacing: 10
        leftMargin: 5
        rightMargin: 5
        topMargin: 5
        bottomMargin: 5

        delegate: ItemDelegate {
            width: 260
            height: modelData.isSpecial ? 60 : 50
            highlighted: ListView.isCurrentItem
            onClicked: {
                leftview.currentIndex = index;
            }

            RowLayout {
                anchors.fill: parent
                Layout.topMargin: 5
                spacing: 10

                Item {
                    Layout.preferredWidth: 1
                }

                Dtk.QtIcon {
                    name: modelData.icon
                    sourceSize: modelData.isSpecial ? "50x50" : "40x40"
                }

                Column {
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    Text {
                        text: modelData.displayName
                        font.pointSize: 14
                        font.bold: true
                    }

                    Text {
                        visible: modelData.isSpecial
                        text: modelData.description
                        font.pointSize: 6
                        color: "gray"
                    }

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

    Component {
        id: baseViewComponent

        Loader {
            id: baseLoader

            source: page.model[leftview.currentIndex].url

            Binding {
                target: baseLoader.item
                property: "width"
                value: page.width - leftview.width
            }

            Binding {
                target: baseLoader.item
                property: "height"
                value: page.height
            }

            Binding {
                target: baseLoader.item
                property: "rootModel"
                value: page.model[leftview.currentIndex]
                restoreMode: Binding.RestoreNone
            }

        }

    }

    Component {
        id: vViewComponent

        PageLoaderV {
            model: page.model[leftview.currentIndex]
            pageHeight: page.height
            pageWidth: page.width - leftview.width
        }

    }

    Component {
        id: welcomedefault

        WelcomePage {
            height: page.height
            width: page.width - leftview.width
        }

    }

    Component {
        id: hViewComponent

        PageLoaderH {
            model: page.model[leftview.currentIndex]
            pageHeight: page.height
            pageWidth: page.width - leftview.width
        }

    }

    Loader {
        sourceComponent: {
            if (leftview.currentIndex < 0)
                return welcomedefault;

            if (page.model[leftview.currentIndex].type === "base")
                return baseViewComponent;

            if (page.model[leftview.currentIndex].type === "vmodule")
                return vViewComponent;

            return hViewComponent;
        }
    }

}
