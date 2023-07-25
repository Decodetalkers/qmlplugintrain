import Marine.Global 1.0
import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import org.deepin.dtk 1.0 as Dtk

ScrollView {
    id: topp

    property alias model: repeat.model
    readonly property int gridSpacing: 20
    readonly property int elementHeight: 100
    readonly property int elementWidth: 400
    readonly property int elementHeightWidthSpacing: topp.gridSpacing + topp.elementHeight
    readonly property int elementWidthWidthSpacing: topp.gridSpacing + topp.elementWidth

    signal clickElemented(int index)

    anchors.centerIn: parent

    Control {
        id: control

        property int layerwidth: {
            if (topp.width < topp.elementWidth + topp.gridSpacing)
                return topp.elementWidth + topp.gridSpacing;

            var length = topp.model.length;
            if (topp.width > 2000 && length > 10)
                return 2000;

            var maxwidth = length * (topp.elementWidth + topp.gridSpacing) - topp.gridSpacing;
            var windowmax = topp.width - (topp.width + topp.gridSpacing) % (topp.elementWidth + topp.gridSpacing);
            return maxwidth > windowmax ? windowmax : maxwidth;
        }

        topPadding: 10
        leftPadding: (topp.width - control.layerwidth) / 2
        rightPadding: (topp.width - control.layerwidth) / 2
        width: topp.width
        height: {
            var len = topp.model.length;
            var itemcount = topp.width / 200;
            if (layout.isSpecial) {
                var realcount = len + 1;
                var h = realcount / itemcount;
                if (h % 1 == 0)
                    h = h | 0;
                else
                    h = h | 0 + 1;
                if (h == 1)
                    return 2 * topp.elementHeightWidthSpacing;

                return h * topp.elementHeightWidthSpacing;
            }
            return len / itemcount * topp.elementHeightWidthSpacing;
        }

        contentItem: GridLayout {
            id: layout

            property bool isSpecial: topp.model.length > 0 ? topp.model[0].isSpecial : false

            columnSpacing: 20
            rowSpacing: 20

            Repeater {
                id: repeat

                Rectangle {
                    width: topp.elementWidth
                    height: {
                        if (index == 0 && modelData.isSpecial)
                            return topp.elementHeight * 2 + topp.gridSpacing;

                        return topp.elementHeight;
                    }
                    Layout.column: {
                        if (index == 0)
                            return 0;

                        var itemcount = (control.layerwidth + topp.gridSpacing) / topp.elementWidthWidthSpacing;
                        if (index < itemcount)
                            return index;

                        if (layout.isSpecial) {
                            var realindex = index + 1;
                            return realindex % itemcount;
                        }
                        return index % itemcount;
                    }
                    Layout.row: {
                        if (index == 0)
                            return 0;

                        var itemcount = (control.layerwidth + topp.gridSpacing) / topp.elementWidthWidthSpacing;
                        if (index < itemcount)
                            return 0;

                        if (layout.isSpecial) {
                            var realindex = index + 1;
                            return realindex / itemcount;
                        }
                        return index / itemcount;
                    }
                    Layout.columnSpan: 1
                    Layout.rowSpan: {
                        if (index == 0 && layout.isSpecial)
                            return 2;

                        return 1;
                    }

                    Button {
                        anchors.fill: parent
                        onClicked: {
                            topp.clickElemented(index);
                        }
                        ColumnLayout {
                            anchors.fill: parent
                            visible: index == 0 && layout.isSpecial
                            Dtk.QtIcon {
                                Layout.alignment: Qt.AlignHCenter
                                name: modelData.icon
                                sourceSize: "80x80"
                            }
                            Text {
                                Layout.alignment: Qt.AlignHCenter
                                text: modelData.displayName
                                font.pointSize: 20
                                font.bold: true
                            }

                            Text {
                                Layout.alignment: Qt.AlignHCenter
                                text: modelData.description
                                font.pointSize: 10
                                color: "gray"
                            }
                            Item {
                                Layout.preferredHeight: 10
                            }

                        }
                        RowLayout {
                            visible: index != 0 || !layout.isSpecial
                            anchors.fill: parent
                            Item {
                                Layout.preferredWidth: 10
                            }
                            Dtk.QtIcon {
                                name: modelData.icon
                                sourceSize: "60x60"
                            }
                            ColumnLayout {
                                Layout.alignment: Qt.AlignVCenter
                                Layout.fillWidth: true
                                Text {
                                    text: modelData.displayName
                                    font.pointSize: 20
                                    font.bold: true
                                }

                                Text {
                                    text: modelData.description
                                    font.pointSize: 10
                                    color: "gray"
                                }
                            }
                            Item {
                                Layout.fillWidth: true
                            }
                        }

                    }

                }

            }

        }

    }

}
