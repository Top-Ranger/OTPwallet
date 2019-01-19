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
    title: qsTr("Add entry")

    Flickable {
        anchors.fill: parent
        interactive: true
        clip: true
        contentHeight: column.height
        ScrollBar.vertical: ScrollBar { }

        Column {
            id: column
            anchors.fill: parent
            spacing: 5

            TextField {
                id: name
                anchors.left: parent.left
                anchors.right: parent.right
                placeholderText: qsTr("Entry name")
            }

            TextField {
                id: secret
                anchors.left: parent.left
                anchors.right: parent.right
                placeholderText: qsTr("Secret")
            }

            Button {
                anchors.left: parent.left
                anchors.right: parent.right
                text: qsTr("Add entry")
                onClicked: {
                    entryManager.addEntry(name.text, secret.text)
                    stackView.get(0, StackView.ForceLoad).newEntry = name.text
                    stackView.pop(Qt.resolvedUrl("add.qml"))
                }
            }
        }
    }
}
