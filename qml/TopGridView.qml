import Marine.Global 1.0
import QtQuick 2.4
import QtQuick.Controls 2.15
import org.deepin.dtk 1.0 as Dtk

Control {
    id: topp
    property alias model: contentGrid.model
    signal clickElemented(int index)
    contentItem:Rectangle{
        GridView {
            anchors.centerIn: parent
            width: {
                if (topp.width > 2000) {
                    return 2000
                }
                if (topp.width < 200) {
                    return 200
                }
                return topp.width - topp.width % 200
            }
            height: topp.height
            id: contentGrid
            cellWidth: 200; cellHeight: 200
            topMargin: 10
            delegate: Column {
                width: 200
                height: 200
                Dtk.IconButton {
                    icon {
                        name: modelData.icon
                        //sourceSize: modelData.isSpecial ? "100x100" : "150x100"
                        width: 150
                        height: 150
                        //sourceSize: "150x150"
                    }
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked : topp.clickElemented(index)
                }
                Text {
                    text: modelData.displayName
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }
}
