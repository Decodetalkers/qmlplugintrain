import Marine
import QtQuick
import QtQuick.Controls

Page {
    id: page

    property alias model: head.model
    property alias pageHeight: page.height
    property alias pageWidth: page.width

    Loader {
        sourceComponent: {
            if (header.currentIndex < 0)
                return welcomeDefault;

            if (page.model[header.currentIndex].type === "base")
                return baseView;

            if (page.model[header.currentIndex].type === "vmodule")
                return vViewComponent;

            return hViewComponent;
        }
    }

    Component {
        id: baseView

        Loader {
            source: page.model[header.currentIndex].url
        }

    }

    Component {
        id: vViewComponent

        PageLoaderV {
            model: page.model[header.currentIndex]
            pageHeight: page.height - header.height
            pageWidth: page.width
        }

    }

    Component {
        id: welcomeDefault

        Text {
            text: "welcome"
        }

    }

    Component {
        id: hViewComponent

        PageLoaderH {
            model: page.model[header.currentIndex]
            pageHeight: page.height - header.height
            pageWidth: page.width
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
