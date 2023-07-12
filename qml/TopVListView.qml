import "."
import QtQuick 2.15
import QtQuick.Controls 2.15
import org.deepin.dtk 1.0 as Dtk

Row {
    id: page

    property alias model: leftview.model

    Rectangle {
        color: Dtk.DTK.palette.shadow
        width: leftview.width
        height: leftview.height

        ListView {
            id: leftview

            height: page.height
            width: 260
            focus: true
            spacing: 10
            leftMargin: 5
            rightMargin: 5
            topMargin: 5
            bottomMargin: 5

            delegate: ItemDelegate {
                width: 250
                height: modelData.isSpecial ? 70 : 60
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
                        sourceSize: modelData.isSpecial ? "60x60" : "50x50"
                    }

                    Column {
                        Text {
                            text: modelData.displayName
                        }

                        Text {
                            visible: modelData.isSpecial
                            text: modelData.description
                            color: "gray"
                        }

                    }

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
