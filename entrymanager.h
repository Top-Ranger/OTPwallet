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


#ifndef ENTRYMANAGER_H
#define ENTRYMANAGER_H

#include <QObject>
#include <QDBusConnection>
#include <QStringList>
#include "common.h"

class EntryManager : public QObject
{
    Q_OBJECT
public:
    explicit EntryManager(QObject *parent = nullptr);
    ~EntryManager();

    Q_INVOKABLE QStringList getAllEntries();
    Q_INVOKABLE bool removeEntry(QString name);
    Q_INVOKABLE bool addEntry(QString name, QString secret);
    Q_INVOKABLE QString getSecret(QString name);

    Q_INVOKABLE void aboutQt();

signals:

public slots:
    void getDisconnectSignal();
    void getDisconnectSignal(int handle);
    void getDisconnectSignal(QString wallet, QString application);

private:
    void showError(QString error);
    void criticalError(QString error);
    void connectToDbus();
    void disconnectFromDbus();
    void createFolders();

    QDBusConnection _dbus;
    qlonglong _handle;
    QString _wallet;
    static const char* NAME;
};

#endif // ENTRYMANAGER_H
