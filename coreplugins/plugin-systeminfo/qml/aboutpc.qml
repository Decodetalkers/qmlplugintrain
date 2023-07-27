// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import "aboutThisPc" as AboutThisPc
import Marine.Control 1.0
import SystemInfo.Base 1.0

import org.deepin.dtk 1.0 as Dtk

ScrollablePage {
    property ModuleModelBase rootModel
    id: root
    Component.onCompleted: {
        AboutMyPc.active()
    }
    ColumnLayout {
        id: column
        spacing: 30
        anchors.horizontalCenter: parent.horizontalCenter

        AboutThisPc.PcImage {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: 250
            Layout.preferredHeight: 250
        }

        AboutThisPc.HostName {
            Layout.alignment: Qt.AlignHCenter
            implicitWidth: root.width > 1500 ? 1400 : root.width - 100
        }

        AboutThisPc.SystemInfo {
            Layout.alignment: Qt.AlignHCenter
            implicitWidth: root.width > 1500 ? 1400 : root.width - 100
        }

    }
    footer: ColumnLayout {
        Item {
            Layout.preferredHeight: 5
        }
        RowLayout {
            Item {
                Layout.fillWidth: true
            }
            Dtk.QtIcon {
                source: AboutMyPc.logo
                sourceSize: "100x20"
            }
            Label {
                text: AboutMyPc.copyright
                font.pointSize: 12
                font.bold: true
            }
            Item {
                Layout.fillWidth: true
            }
        }
        Item {
            Layout.preferredHeight: 5
        }
    }
}
