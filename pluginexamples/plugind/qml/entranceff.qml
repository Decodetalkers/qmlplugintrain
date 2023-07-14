import Marine.Model 1.0
import PluginB.Global 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    property ModuleModelBase rootModel

    Text {
        text: "Greate!!!!!!!!!!!!!"
    }

    Button {
        text: "Let's test it"
        onClicked: {
            rootModel.isNotify = !rootModel.isNotify;
        }
    }

}
