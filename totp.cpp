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

#include "totp.h"
#include <QDateTime>

#include <QProcess>

TOTP::TOTP(QObject *parent) : QObject(parent),
    _secret("")
{

}

void TOTP::setSecret(QString secret)
{
    _secret = secret.remove(' ');
}

uint TOTP::remainingTime()
{
    return 30 - QDateTime::currentDateTime().toTime_t() % 30;
}

QString TOTP::otp()
{
    QProcess *python = new QProcess();
    python->deleteLater();
    python->start(QString("/usr/bin/python3 -c \"import pyotp; token = input(); print(pyotp.TOTP(token).now())\""));
    python->write(_secret.toLatin1());
    python->write("\n");
    python->waitForFinished(-1);
    if(python->exitStatus() != QProcess::NormalExit)
    {
        WARNING(python->readAllStandardError());
        return "Python process crashed";
    }
    return python->readAllStandardOutput();
}
