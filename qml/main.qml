import Marine.Global 1.0
import Marine
import QtQuick.Controls
import QtQuick
ApplicationWindow {
    visible: true
    Connections {
        function onUrlLoader(url) {
            console.log(url)
            console.log(PluginLoader.modules)
            console.log(PluginLoader.modules[0])
        }
        target: PluginLoader
    }
    //GridView {
    //    width: parent.width
    //    height: parent.height
    //    model: ListModel {
    //        id: model
    //    }
    //    delegate: Button {
    //        text: model.name
    //        width: 300
    //        height: 300
    //    }
    //}
    VListView {
        model: PluginLoader.modules
    }
}
