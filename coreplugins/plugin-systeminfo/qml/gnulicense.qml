
// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import SystemInfo.Base 1.0
import QtQuick 2.15
import QtQuick.Layouts 1.11
import Marine.Model 1.0

ScrollabelPage {
    id: root
    property ModuleModelBase rootModel
    Component.onCompleted: {
        LicenseObject.active()
    }
    ColumnLayout {
        id: column
        spacing: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            Layout.alignment: Qt.AlignHCenter
            text: LicenseObject.gnuLicenseTitle
        }
        Text {
            text: LicenseObject.gnuLicense
            wrapMode: Text.Wrap
            Layout.preferredWidth: column.width
        }

    }
}
