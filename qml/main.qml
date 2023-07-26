import Marine.Global 1.0
import QtQuick 2.4
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import org.deepin.dtk 1.0 as Dtk

Dtk.ApplicationWindow {
    visible: true
    minimumWidth: 1000
    Dtk.DWindow.enabled: true

    TopGridView {
        id: mainGridView
        anchors.fill: parent
        model: PluginLoader.modules
        onClickElemented :function (index) {
            mainGridView.visible = false
            mainlistview.setIndex(index)
            mainlistview.visible = true
        }
    }

    TopVListView {
        id: mainlistview
        visible: false
        anchors.fill: parent
        model: PluginLoader.modules
    }

    header: Dtk.TitleBar {
        id: header
        enableInWindowBlendBlur: true

        leftContent : RowLayout {
            spacing: 10
            Dtk.IconButton {
                id: unshow
                icon.name: "window_sidebar"
                visible: mainlistview.visible
                enabled: mainlistview.visible
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
                visible: mainlistview.visible
                enabled: mainlistview.visible
                hoverEnabled: true
                Dtk.ToolTip {
                    visible: preBtn.hovered
                    text: qsTr("Previous page")
                }

                onClicked: {
                    mainlistview.visible = false
                    mainGridView.visible = true
                }
            }
        }
        content: Item {
            Dtk.SearchEdit {
                id: searchedit
                width: 300
                anchors.centerIn: parent
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
                    PluginLoader.resetModel()
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
                    mainGridView.visible = false
                    mainlistview.visible = true
                    mainlistview.jump(model.routine)
                }
            }
        }
    }

}
