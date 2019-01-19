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

Page {
    title: qsTr("OTPwallet")

    property string newEntry: ""

    onActiveFocusChanged: {
        if (newEntry !== "") {
            entryList.append({"entryName": newEntry})
            newEntry = ""
        }
    }

    Component.onCompleted: {
        var entries = entryManager.getAllEntries()
        for(var i = 0; i < entries.length; i++) {
            entryList.append({"entryName": entries[i]})
        }
    }

    ListView {
        anchors.fill: parent
        model: entryList

        ScrollBar.vertical: ScrollBar { }

        spacing: 5

        header: Button {
            anchors.left: parent.left
            anchors.right: parent.right
            text: qsTr("Add entry")
            onClicked: stackView.push(Qt.resolvedUrl("add.qml"))
        }

        footer: Button {
            anchors.left: parent.left
            anchors.right: parent.right
            text: qsTr("About")
            onClicked: stackView.push(Qt.resolvedUrl("about.qml"))
        }

        delegate: Component {
            Rectangle {
                 color: entryMouseArea.containsMouse ? "grey" : "lightgrey"
                 anchors.left: parent.left
                 anchors.right: parent.right
                 height: 3 * entryText.font.pixelSize
                 Text {
                     id: entryText
                     anchors.centerIn: parent
                     text: entryName
                     opacity: 1
                     color: "black"
                 }
                 MouseArea {
                     id: entryMouseArea
                     anchors.fill: parent
                     hoverEnabled: true
                     onClicked: stackView.push(Qt.resolvedUrl("otp.qml"), {"entry": entryName})
                 }
             }
        }
    }

    ListModel {
        id: entryList
    }
}
