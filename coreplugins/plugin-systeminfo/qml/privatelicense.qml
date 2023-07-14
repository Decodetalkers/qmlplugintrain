// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import SystemInfo.Base 1.0
import QtQuick 2.15
import QtQuick.Layouts 1.11
import Marine.Model 1.0

ScrollabelPage {
    property ModuleModelBase rootModel
    id: root
    ColumnLayout {
        id: column
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            text: LicenseObject.privateLicenseTitle
            Layout.alignment: Qt.AlignHCenter
        }
        Text {
            text: LicenseObject.privateLicense
            wrapMode: Text.Wrap
            Layout.preferredWidth: column.width
            onLinkHovered: {
                // TODO: hover open link
                // console.log("hovered")
            }
            onLinkActivated: function(link) {
                Qt.openUrlExternally(link)
            }
        }

    }
}
