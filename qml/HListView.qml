import "components"

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQml 2.15

Page {
    id: page

    property alias model: head.model
    property alias pageHeight: page.height
    property alias pageWidth: page.width

    Loader {
        id: loader
        sourceComponent: {
            if (head.currentIndex < 0)
                return welcomeDefault;

            if (page.model[head.currentIndex].type === "base")
                return baseView;

            if (page.model[head.currentIndex].type === "vmodule")
                return vViewComponent;

            return hViewComponent;
        }
    }

    function jump(index) {
        head.currentIndex = index[0]
        index.shift()
        if (index.length > 0) {
            if (page.model[head.currentIndex].type === "vmodule") {
                loader.item.jump(index);
                return
            }
            if (page.model[head.currentIndex].type === "hmodule")
                loader.item.jump(index);
        }
    }

    Component {
        id: baseView

        Loader {
            id: baseLoader

            source: page.model[head.currentIndex].url

            Binding {
                target: baseLoader.item
                property: "width"
                value: page.width
            }

            Binding {
                target: baseLoader.item
                property: "height"
                value: page.height - header.height
            }

            Binding {
                target: baseLoader.item
                property: "rootModel"
                value: page.model[head.currentIndex]
                restoreMode: Binding.RestoreBindingOrValue
            }

        }

    }

    Component {
        id: vViewComponent

        PageLoaderV {
            model: page.model[head.currentIndex]
            pageHeight: page.height - header.height
            pageWidth: page.width
        }

    }

    Component {
        id: welcomeDefault

        WelcomePage {
            height: header.height ?  page.height - header.height : page.height
            width: page.width
        }

    }

    Component {
        id: hViewComponent

        PageLoaderH {
            model: page.model[head.currentIndex]
            pageHeight: page.height - header.height
            pageWidth: page.width
        }

    }

    header: CustomTabBar {
        id: head
    }
}
