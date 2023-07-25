import Marine.Global 1.0
import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import org.deepin.dtk 1.0 as Dtk

ScrollView {
    id: topp

    property alias model: repeat.model

    signal clickElemented(int index)

    anchors.centerIn: parent

    Control {
        id: control

        property int layerwidth: {
            if (topp.width < 200)
                return 200;

            var length = topp.model.length;
            if (topp.width > 2000 && length > 10)
                return 2000;

            var maxwidth = length * 200;
            var windowmax = topp.width - topp.width % 200;
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
                    return 400;

                return h * 200;
            }
            return len / itemcount * 200;
        }

        contentItem: GridLayout {
            id: layout

            property bool isSpecial: topp.model.length > 0 ? topp.model[0].isSpecial : false

            columnSpacing: 0
            rowSpacing: 0

            Repeater {
                id: repeat

                Rectangle {
                    width: 200
                    height: {
                        if (index == 0 && modelData.isSpecial)
                            return 400;

                        return 200;
                    }
                    Layout.column: {
                        if (index == 0)
                            return 0;

                        var itemcount = control.layerwidth / 200;
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

                        var itemcount = control.layerwidth / 200;
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

                        icon {
                            name: modelData.icon
                            width: 200
                            height: {
                                if (index == 0 && modelData.isSpecial)
                                    return 400;

                                return 200;
                            }
                        }

                    }

                }

            }

        }

    }

}
