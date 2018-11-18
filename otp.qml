/* SPDX-License-Identifier: GPL-3.0-or-later
 *
 * Copyright (C) 2018  Marcus Soll
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

import QtQuick 2.9
import QtQuick.Controls 2.2
import com.github.top_ranger.OTPwallet.TOTP 1.0

Page {
    property string entry: ""
    property string otp: ""
    property int timestep: 30
    property int remainingTime: 30

    TOTP {
        id: totp
    }

    Timer {
        id: timer
        interval: 1000
        repeat: true
        onTriggered: updateOtp()
    }

    Component.onCompleted: {
        var secret = entryManager.getSecret(entry)
        totp.setSecret(secret)
        updateOtp()
        timer.start()
    }

    function updateOtp() {
        otp = totp.otp()
        remainingTime = totp.remainingTime()
    }

    title: qsTr("TOTP") + " " + entry

    Flickable {
        anchors.fill: parent
        interactive: true
        clip: true
        contentHeight: column.height
        ScrollBar.vertical: ScrollBar { }

        Column {
            id: column
            anchors.fill: parent
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: 5

            Label {
                id: labelName
                anchors.left: parent.left
                anchors.right: parent.right

                text: entry
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                id: labelOTP
                anchors.left: parent.left
                anchors.right: parent.right

                text: otp
                font.pixelSize: 2 * labelName.font.pixelSize
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
            }

            ProgressBar {
                anchors.left: parent.left
                anchors.right: parent.right
                value: remainingTime / timestep
            }
        }
    }
}
