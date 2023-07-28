import Marine.Control 1.0
import QtQuick 2.15
import QtQuick.Layouts 1.11

ScrollablePage {
    property ModuleModelBase rootModel
    ColumnLayout {
        anchors.fill: parent
        DccClock {
            Layout.alignment : Qt.AlignHCenter
            shift: 8
        }

        Item {
            Layout.fillHeight: true
        }
    }

}
