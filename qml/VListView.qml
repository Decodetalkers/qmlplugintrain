import Marine
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Row {
    id: page

    property alias model: leftview.model

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
        id: defaults

        Loader {
            source: page.model[leftview.currentIndex].url
        }
    }

    Component {
        id: defaults2

        PageLoader {
            model: page.model[leftview.currentIndex]
        }

    }

    Component {
        id: defaults3

        Text {
            text: "welcome"
        }

    }

    Loader {
        sourceComponent: leftview.currentIndex < 0 ? defaults3 : page.model[leftview.currentIndex].type == "base" ? defaults : defaults2
    }

}
