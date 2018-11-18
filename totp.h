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

#ifndef TOTP_H
#define TOTP_H

#include <QObject>
#include "common.h"

class TOTP : public QObject
{
    Q_OBJECT
public:
    explicit TOTP(QObject *parent = nullptr);
    explicit TOTP(QString secret, QObject *parent = nullptr);

    Q_INVOKABLE void setSecret(QString secret);
    Q_INVOKABLE uint remainingTime();
    Q_INVOKABLE QString otp();

signals:

public slots:

private:
    QString _secret;
};

#endif // TOTP_H
