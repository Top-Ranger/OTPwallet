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
