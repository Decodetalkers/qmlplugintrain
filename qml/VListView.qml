import QtQuick.Controls
import QtQuick.Layouts
import QtQuick

Row {
    property alias model: left.model
    ListView {
        id: left
        width: 300
        height: 300
        delegate: contactDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }

    Component {
        id: contactDelegate
        Item {
            width: 180; height: 40
            Column {
                Text { text: modelData.displayName }
                Text { text: modelData.description }
            }
        }
    }
    Text { text: "aa" }
}
