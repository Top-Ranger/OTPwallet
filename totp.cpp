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
