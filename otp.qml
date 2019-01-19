/* SPDX-License-Identifier: Apache-2.0
 *
 * Copyright 2018,2019 Marcus Soll
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
