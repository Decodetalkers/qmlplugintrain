import Marine.Global 1.0
import QtQuick 2.4
import QtQuick.Controls 2.4
import org.deepin.dtk 1.0 as Dtk

Dtk.ApplicationWindow {
    visible: true
    Dtk.DWindow.enabled: true

    TopVListView {
        anchors.fill: parent
        model: PluginLoader.modules
    }

    header: Dtk.TitleBar {
        id: searchedit
        enableInWindowBlendBlur: true

        content: Item {
            Dtk.SearchEdit {
                anchors.centerIn: parent
                width: 300
                onTextChanged: {
                    menu.open()
                    PluginLoader.getModel(text)
                }
                onAccepted: {
                    menu.close()
                    PluginLoader.getModel("")
                }

            }
        }

    }

    Menu {
        id: menu
        width: 300
        x: searchedit.width / 2 - 165
        y: searchedit.y + searchedit.height
        Repeater {
            model: PluginLoader.searchPattern
            MenuItem {
                text: model.displayName
            }
        }
    }

}
