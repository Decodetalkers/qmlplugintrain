import SystemInfo.Base 1.0
import QtQuick 2.15

Image {
    fillMode: Image.PreserveAspectFit
    source: {
        if (AboutMyPc.isLaptop) 
            return "qrc:/resources/icon_about_laptop.svg"

        return "qrc:/resources/icon_about_pc.svg"
    }
}
