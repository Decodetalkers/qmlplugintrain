import Marine.Model 1.0
import PluginA.Global 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    property ModuleModelBase rootModel

    Column {
        Text {
            text: GlobalConst.name
        }

        Button {
            text: "sss"
            onClicked: {
                console.log(rootModel.isNotify);
                rootModel.isNotify = !rootModel.isNotify;
            }
        }

    }

}
