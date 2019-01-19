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

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "entrymanager.h"
#include "totp.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    qmlRegisterType<TOTP>("com.github.top_ranger.OTPwallet.TOTP", 1, 0, "TOTP");

    EntryManager entryManager;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("entryManager", &entryManager);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
