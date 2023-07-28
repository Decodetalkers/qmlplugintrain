// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import SystemInfo.Base 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import Marine.Control 1.0

GroupBox {
    ColumnLayout {
        spacing: 1
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter

        SettingRowLayout {
            Layout.fillWidth: true

            Label {
                text: qsTr("edition: ")
                Layout.fillWidth: true
            }

            Label {
                text: AboutMyPc.edition
            }

        }

        SettingRowLayout {
            Layout.fillWidth: true

            Label {
                text: qsTr("type: ")
                Layout.fillWidth: true
            }

            Label {
                text: AboutMyPc.cputype
            }

        }

        SettingRowLayout {
            Layout.fillWidth: true

            Label {
                text: qsTr("processor: ")
                Layout.fillWidth: true
            }

            Label {
                text: AboutMyPc.processor
            }

        }

        SettingRowLayout {
            Layout.fillWidth: true

            Label {
                text: qsTr("memory: ")
                Layout.fillWidth: true
            }

            Label {
                text: AboutMyPc.memory
            }

        }

        SettingRowLayout {
            Layout.fillWidth: true

            Label {
                text: qsTr("Graphics Platform: ")
                Layout.fillWidth: true
            }

            Label {
                text: AboutMyPc.graphicsPlatform
            }

        }

        SettingRowLayout {
            Layout.fillWidth: true

            Label {
                text: qsTr("kernel: ")
                Layout.fillWidth: true
            }

            Label {
                text: AboutMyPc.kernel
            }

        }

    }

    background: Rectangle {
        radius: 5
        color: "transparent"
    }

}
