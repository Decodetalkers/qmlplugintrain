import Marine.Model 1.0
import PluginB.Global 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    property ModuleModelBase rootModel

    Column {
        Text {
            text: GlobalConst.name
        }

        Button {
            text: "Test it!!!"
            onClicked: {
                rootModel.isNotify = !rootModel.isNotify;
            }
        }

    }

}
