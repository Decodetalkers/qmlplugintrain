import Marine.Global 1.0
import QtQuick.Controls
import QtQuick
ApplicationWindow {
    visible: true
    Connections {
        function onUrlLoader(url) {
            console.log(url)
            model.append({
                name: "sss",
                url: url
            })
        }
        target: PluginLoader
    }
    GridView {
        width: parent.width
        height: parent.height
        model: ListModel {
            id: model
        }
        delegate: Button {
            text: model.name
            width: 300
            height: 300
        }
    }
    //StackView {
    //    id: stackView
    //    anchors.fill: parent
    //    initialItem: Pane {
    //        Text {
    //            text: "sss"
    //        }
    //    }
    //}
}
