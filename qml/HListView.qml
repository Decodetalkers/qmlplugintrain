import "components"

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1

import QtQml 2.15
Page {
    id: page

    property alias model: head.model
    property alias pageHeight: page.height
    property alias pageWidth: page.width

    Loader {
        id: loader
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

    function jump(index) {
        header.currentIndex = index[0]
        index.shift()
        if (index.length > 0) {
            if (page.model[header.currentIndex].type === "vmodule") {
                loader.item.jump(index);
                return
            }
            if (page.model[header.currentIndex].type === "hmodule")
                loader.item.jump(index);
        }
    }

    Component {
        id: baseView

        Loader {
            id: baseLoader

            source: page.model[header.currentIndex].url

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
                value: page.model[header.currentIndex]
                restoreMode: Binding.RestoreBindingOrValue
            }

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

        WelcomePage {
            height: header.height ?  page.height - header.height : page.height
            width: page.width
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
                contentItem: RowLayout {
                    Label {
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                        text: modelData.displayName
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

    }

}
