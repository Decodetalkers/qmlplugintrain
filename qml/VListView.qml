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

        Text {
            text: "ss"
        }

    }

    Component {
        id: defaults2

        Text {
            text: "bb"
        }

    }

    Loader {
        sourceComponent: leftview.currentIndex == 1 ? defaults : defaults2
    }
    //PageLoader {

}
