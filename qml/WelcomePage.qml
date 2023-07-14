import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

import org.deepin.dtk 1.0 as Dtk

ColumnLayout {
    anchors.horizontalCenter: parent.horizontalCenter
    Dtk.QtIcon {
        Layout.alignment : Qt.AlignHCenter
        name: "firefox"
        sourceSize: "100x100"
    }
    Text {
        Layout.alignment : Qt.AlignHCenter
        text: "Welcome"
    }
}
