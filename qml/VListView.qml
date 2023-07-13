import "."
import QtQuick 2.15
import QtQuick.Controls 2.15
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
        width: 270
        focus: true
        spacing: 10
        leftMargin: 5
        rightMargin: 5
        topMargin: 5
        bottomMargin: 5

        delegate: ItemDelegate {
            width: 260
            height: modelData.isSpecial ? 80 : 70
            highlighted: ListView.isCurrentItem
            onClicked: {
                leftview.currentIndex = index;
            }

            Row {
                topPadding: 5
                leftPadding: 10
                spacing: 10

                Dtk.QtIcon {
                    name: modelData.icon
                    sourceSize: modelData.isSpecial ? "70x70" : "60x60"
                }

                Column {
                    anchors.verticalCenter: parent.verticalCenter
                    Text {
                        text: modelData.displayName
                        font.pointSize: 15
                        font.bold: true

                    }

                    Text {
                        visible: modelData.isSpecial
                        text: modelData.description
                    }

                }

                Text {
                    text: "o"
                    visible: modelData.isNotify
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

        Text {
            text: "welcome"
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
