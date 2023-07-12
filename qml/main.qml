import "."
import Marine.Global 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import org.deepin.dtk 1.0 as Dtk

Dtk.ApplicationWindow {
    visible: true
    Dtk.DWindow.enabled: true

    TopVListView {
        anchors.fill: parent
        model: PluginLoader.modules
    }

    header: Dtk.TitleBar {
        enableInWindowBlendBlur: true

        content: Item {
            Dtk.SearchEdit {
                anchors.centerIn: parent
                width: 300
            }

        }

    }

}
