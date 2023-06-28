import Marine.Global 1.0
import QtQuick.Controls
import QtQuick
ApplicationWindow {
    visible: true
    Connections {
        function onUrlLoader(url) {
            console.log(url)
            stackView.push(url)
        }
        target: PluginLoader
    }
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Pane {
            Text {
                text: "sss"
            }
        }
    }
}
