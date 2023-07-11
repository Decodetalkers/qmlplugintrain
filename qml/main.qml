import Marine.Global 1.0
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true

    VListView {
        anchors.fill: parent
        model: PluginLoader.modules
    }

}
