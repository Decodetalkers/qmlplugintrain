import Marine
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Row {
    id: page

    property alias model: leftview.model

    height: 1000

    ListView {
        id: leftview

        height: parent.height
        width: 100
        focus: true

        delegate: ItemDelegate {
            width: 100
            height: 50
            highlighted: ListView.isCurrentItem
            onClicked: {
                leftview.currentIndex = index;
            }

            Column {
                Text {
                    text: modelData.displayName
                }

                Text {
                    text: modelData.description
                }

            }

        }

    }

    Component {
        id: baseViewComponent

        Loader {
            source: page.model[leftview.currentIndex].url
        }

    }

    Component {
        id: vViewComponent

        PageLoaderV {
            model: page.model[leftview.currentIndex]
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
        }

    }

    Loader {
        sourceComponent: {
            if (leftview.currentIndex < 0)
                return welcomedefault;

            if (page.model[leftview.currentIndex].type === "base")
                return baseViewComponent;

            if (page.model[leftview.currentIndex].type == "vmodule")
                return vViewComponent;

            return hViewComponent;
        }
    }

}
