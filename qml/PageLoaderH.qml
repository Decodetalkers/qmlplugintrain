import Marine.Model 1.0
import QtQuick 2.15

Loader {
    id: loader

    required property ModuleModel model
    required property int pageHeight
    required property int pageWidth

    source: "HListView.qml"

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

    function jump(index) {
        loader.item.jump(index)
    }
}
