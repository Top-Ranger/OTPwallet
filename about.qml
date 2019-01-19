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
    title: qsTr("About")

    Flickable {
        anchors.fill: parent
        interactive: true
        clip: true
        contentHeight: text.height
        ScrollBar.vertical: ScrollBar { }

        Text {
            id: text
            anchors.left: parent.left
            anchors.right: parent.right

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.Wrap
            textFormat: Text.RichText
            onLinkActivated: entryManager.aboutQt()
            text: "<div><h1>OTPwallet</h1></div>
<div><i>Copyright (C) 2018 Marcus Soll</i></div>
<br>
<div>This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.</div>
<br>
<div>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.</div>
<br>
<div>You should have received a copy of the GNU General Public License along with this program.  If not, see https://www.gnu.org/licenses/.</div>
<div><h1>About Qt</h1></div>
<div>This program uses Qt - for more information click <a href=\"about:qt\">here</a></div>
<div><h1>About PyOTP</h1><div>
<div>This program uses PyOTP, which is licensed under the MIT licence - for more information see your local installation of PyOTP.</div>"
        }
    }
}
