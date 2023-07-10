import Marine
import Marine.Global 1.0
import QtQuick.Controls

ApplicationWindow {
    visible: true

    VListView {
        anchors.fill: parent
        model: PluginLoader.modules
    }

}
