import Marine.Model
import QtQuick

Loader {
    id: loader

    required property ModuleModel model
    required property int pageHeight
    required property int pageWidth

    source: "VListView.qml"

    Binding {
        target: loader.item
        property: "model"
        value: model.models
    }

    Binding {
        target: loader.item
        property: "pageWidth"
        value: loader.pageWidth
    }

    Binding {
        target: loader.item
        property: "pageHeight"
        value: loader.pageHeight
    }

}
