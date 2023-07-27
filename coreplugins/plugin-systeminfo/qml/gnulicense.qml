
// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import SystemInfo.Base 1.0
import QtQuick 2.15
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15
import Marine.Control 1.0

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

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: LicenseObject.gnuLicenseTitle
        }
        Label {
            text: LicenseObject.gnuLicense
            wrapMode: Text.Wrap
            Layout.preferredWidth: column.width
        }

    }
}
