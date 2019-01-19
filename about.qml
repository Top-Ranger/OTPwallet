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
<div><i>Copyright 2018,2019 Marcus Soll</i></div>
<br>
<div>Licensed under the Apache License, Version 2.0 (the \"License\"); you may not use this file except in compliance with the License.</div>
<br>
<div>Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an \"AS IS\" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.</div>
<div><h1>About Qt</h1></div>
<div>This program uses Qt - for more information click <a href=\"about:qt\">here</a></div>
<div><h1>About PyOTP</h1><div>
<div>This program uses PyOTP, which is licensed under the MIT licence - for more information see your local installation of PyOTP.</div>"
        }
    }
}
