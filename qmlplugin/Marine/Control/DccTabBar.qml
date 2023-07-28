import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import org.deepin.dtk 1.0 as Dtk

ScrollView {
    id: page

    default property alias content: corelayout.children

    clip: true

    Control {
        id: control

        width: page.width
        topPadding: 2
        bottomPadding: 2

        contentItem: RowLayout {
            id: header

            Item {
                Layout.fillWidth: true
            }

            Control {
                id: corecontrol

                leftPadding: 3
                rightPadding: 3
                topPadding: 3
                bottomPadding: 3

                background: Dtk.BoxPanel {
                    width: corecontrol.width
                    height: corecontrol.height
                }

                contentItem: RowLayout {
                    id: corelayout
                }

            }

            Item {
                Layout.fillWidth: true
            }

        }

    }

}
