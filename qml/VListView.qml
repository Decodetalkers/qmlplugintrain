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
        clip: true

        delegate: ItemDelegate {
            id: dl
            width: 260
            height: modelData.isSpecial ? 60 : 50
            property int textWidth: modelData.isSpecial ? width - 95 : width - 85
            checked: ListView.isCurrentItem
            highlighted: ListView.isCurrentItem
            onClicked: {
                leftview.currentIndex = index;
            }
            TextMetrics {
                id: description
                elide: Text.ElideRight
                elideWidth: dl.textWidth
                font.pointSize: 6
                text: modelData.description
            }
            TextMetrics {
                id: displayName
                elide: Text.ElideRight
                elideWidth: dl.textWidth
                font.pointSize: 12
                font.bold: true
                text: modelData.displayName
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
                    Label {
                        text: displayName.elidedText
                        font.pointSize: 12
                        font.bold: true
                    }

                    Label {
                        visible: modelData.isSpecial
                        text: description.elidedText
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

    function jump(index) {
        leftview.currentIndex = index[0]
        index.shift()
        if (index.length > 0) {
            if (page.model[leftview.currentIndex].type === "vmodule") {
                loader.item.jump(index);
                return
            }
            if (page.model[leftview.currentIndex].type === "hmodule")
                loader.item.jump(index)
        }
    }

    Loader {
        id: loader
        sourceComponent: {
            if (leftview.currentIndex < 0 || page.model.length === 0)
                return welcomedefault;

            if (page.model[leftview.currentIndex].type === "base")
                return baseViewComponent;

            if (page.model[leftview.currentIndex].type === "vmodule")
                return vViewComponent;

            return hViewComponent;
        }
    }

}
