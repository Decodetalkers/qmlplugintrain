import Marine.Model 1.0
import PluginA.Global 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    property ModuleModelBase rootModel

    Text {
        text: "Greate!!!!!!!!!!!!!"
    }

    Button {
        text: "sss"
        onClicked: {
            console.log(rootModel.isNotify);
            rootModel.isNotify = !rootModel.isNotify;
        }
    }

}
