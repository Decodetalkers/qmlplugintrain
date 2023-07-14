import QtQuick 2.15
import QtQuick.Layouts 1.11

ColumnLayout {
    anchors.horizontalCenter: parent.horizontalCenter
    Item {
        Layout.fillHeight: true
    }
    Image {
        Layout.alignment : Qt.AlignHCenter
        source: "qrc:/icons/deepin.png"
        sourceSize: "100x100"
    }
    Item {
        Layout.preferredHeight: 30
    }
    Text {
        Layout.alignment : Qt.AlignHCenter
        font.pointSize: 10
        text: "Welcome to Deepin Control Center"
    }
    Item {
        Layout.fillHeight: true
    }

}
