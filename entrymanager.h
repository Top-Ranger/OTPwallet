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
