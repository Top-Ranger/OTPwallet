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
                 height: 24
                 Text {
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
