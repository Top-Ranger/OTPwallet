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
