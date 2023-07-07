import Marine
import Marine.Model
import QtQuick

Loader {
    //sourceComponent: model.type == "base" ? textComponent: boolComponent
    //Component {
    //    id: textComponent
    //    NormalPage {
    //        url: model.url
    //    }
    //}

    id: loader

    required property ModuleModel model

    source: "VListView.qml"

    Binding {
        target: loader.item
        property: "model"
        value: model.models
    }

}
