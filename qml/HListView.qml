import Marine
import QtQuick
import QtQuick.Controls

Page {
    id: page

    property alias model: head.model

    height: 1000

    Loader {
        sourceComponent: header.currentIndex < 0 ? defaults3 : page.model[header.currentIndex].type == "base" ? defaults : page.model[header.currentIndex].type == "vmodule" ? defaults2 : defaults4
    }

    Component {
        id: defaults

        Loader {
            source: page.model[header.currentIndex].url
        }

    }

    Component {
        id: defaults2

        PageLoaderV {
            model: page.model[header.currentIndex]
        }

    }

    Component {
        id: defaults3

        Text {
            text: "welcome"
        }

    }

    Component {
        id: defaults4

        PageLoaderH {
            model: page.model[header.currentIndex]
        }

    }

    header: TabBar {
        id: header

        Repeater {
            id: head

            TabButton {
                text: modelData.displayName
            }

        }

    }

}
