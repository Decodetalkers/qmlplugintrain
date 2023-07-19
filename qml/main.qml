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
        id: header
        enableInWindowBlendBlur: true

        content: Item {
            Dtk.SearchEdit {
                id: searchedit
                anchors.centerIn: parent
                width: 300
                onTextChanged: {
                    menu.open()
                    PluginLoader.getModel(text)
                    if (text == "") {
                        searchedit.focus = false
                        menu.close()
                    }
                }
                onAccepted: {
                    searchedit.focus = false
                    menu.close()
                    PluginLoader.getModel("")
                }

            }
        }

    }

    Menu {
        id: menu
        focus: false
        width: 300
        x: header.width / 2 - 165
        y: header.y + header.height
        Repeater {
            model: PluginLoader.searchPattern
            MenuItem {
                text: model.displayName
                onTriggered : {
                    console.log(model.routine)
                }
            }
        }
    }

}
