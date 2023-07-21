import Marine.Global 1.0
import QtQuick 2.4
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import org.deepin.dtk 1.0 as Dtk

Dtk.ApplicationWindow {
    visible: true
    Dtk.DWindow.enabled: true

    TopVListView {
        id: mainlistview
        anchors.fill: parent
        model: PluginLoader.modules
    }

    header: Dtk.TitleBar {
        id: header
        enableInWindowBlendBlur: true

        content: RowLayout {
            spacing: 10
            Dtk.IconButton {
                id: unshow
                icon.name: "arrow_ordinary_left"
                visible: true
                hoverEnabled: true
                onClicked: {
                    mainlistview.leftvisible = !mainlistview.leftvisible
                }
                Dtk.ToolTip {
                    visible: unshow.hovered
                    text: qsTr("unshow the leftview")
                }
            }
            Dtk.IconButton {
                id: preBtn
                icon.name: "arrow_ordinary_left"
                visible: true
                hoverEnabled: true
                onClicked: {
                }

                Dtk.ToolTip {
                    visible: preBtn.hovered
                    text: qsTr("Previous page")
                }
            }
            Dtk.SearchEdit {
                id: searchedit
                Layout.preferredWidth: 300
                Layout.alignment: Qt.AlignCenter
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
                    mainlistview.jump(model.routine)
                }
            }
        }
    }

}
