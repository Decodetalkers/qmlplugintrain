import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Control {
    id: group
    clip: true

    default property alias content: content.children
    property alias title: title.text

    contentItem: ColumnLayout {
        RowLayout {
            Item {
                Layout.preferredWidth: 2
            }
            Label {
                id: title
                font {
                    pointSize: 16
                    bold: true
                }
            }
        }
        ColumnLayout {
            id: content
        }
    }
}
