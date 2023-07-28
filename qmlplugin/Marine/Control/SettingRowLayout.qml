import QtQuick 2.15
import QtQuick.Layouts 1.11
import org.deepin.dtk 1.0 as Dtk

Rectangle {
    default property alias data: row.data

    implicitWidth: row.implicitWidth
    implicitHeight: row.implicitHeight * 2
    color: Dtk.DTK.palette.shadow
    radius: 5
    clip: true

    RowLayout {
        id: row

        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.fill: parent
    }

}
