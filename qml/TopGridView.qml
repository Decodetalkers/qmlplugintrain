import Marine.Global 1.0
import QtQuick 2.4
import org.deepin.dtk 1.0 as Dtk

GridView {
    id: toppp
    signal clickElemented(int index)
    cellWidth: 200; cellHeight: 200
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
            onClicked : toppp.clickElemented(index)
        }
        Text {
            text: modelData.displayName
            anchors.horizontalCenter: parent.horizontalCenter 
        }
    }
}
