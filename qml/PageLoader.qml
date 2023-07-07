import Marine.Model
import QtQuick

Loader {
    id: loader

    required property ModuleModel model

    source: "VListView.qml"

    Binding {
        target: loader.item
        property: "model"
        value: model.models
    }

}
