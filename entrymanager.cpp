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


#include "entrymanager.h"

#include <QDBusMessage>
#include <QDBusError>
#include <QDataStream>
#include <QMessageBox>
#include <QCoreApplication>

const char* EntryManager::NAME = "OTPwallet";

namespace {
QByteArray hashToByte(QHash<QString, QString> hash)
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << hash;
    return array;
}

QHash<QString, QString> byteToHash(QByteArray array)
{
    QHash<QString, QString> hash;
    QDataStream stream(&array, QIODevice::ReadOnly);
    stream >> hash;
    return hash;
}
}

EntryManager::EntryManager(QObject *parent) : QObject(parent),
    _dbus(""),
    _handle(0)
{
    connectToDbus();
}

EntryManager::~EntryManager()
{
    disconnectFromDbus();
}

QStringList EntryManager::getAllEntries()
{
    QDBusMessage updateMessage = QDBusMessage::createMethodCall("org.kde.kwalletd5", "/modules/kwalletd5", "org.kde.KWallet", "entryList");
    updateMessage << (int) _handle << QString(NAME) << QString(NAME);
    QDBusMessage answer = _dbus.call(updateMessage);
    if(answer.type() == QDBusMessage::ErrorMessage)
    {
        QString error = QString(tr("Error while getting entries: %1 - %2")).arg(answer.errorName()).arg(answer.errorMessage());
        WARNING(error);
        showError(error);
        return QStringList();
    }

    return answer.arguments().at(0).toStringList();
}

bool EntryManager::removeEntry(QString name)
{
    QDBusMessage deleteMessage = QDBusMessage::createMethodCall("org.kde.kwalletd5", "/modules/kwalletd5", "org.kde.KWallet", "removeEntry");
    deleteMessage << (int) _handle << QString(NAME) << name << QString(NAME);
    QDBusMessage answer = _dbus.call(deleteMessage);
    if(answer.type() == QDBusMessage::ErrorMessage)
    {
        QString error = QString(tr("Error while removing entry: %1 - %2")).arg(answer.errorName()).arg(answer.errorMessage());
        WARNING(error);
        showError(error);
        return false;
    }
    return true;
}

bool EntryManager::addEntry(QString name, QString secret)
{
    QDBusMessage addMessage = QDBusMessage::createMethodCall("org.kde.kwalletd5", "/modules/kwalletd5", "org.kde.KWallet", "writeMap");
    QHash<QString, QString> entry;
    entry["secret"] = secret;
    addMessage << (int) _handle << QString(NAME) << name << hashToByte(entry) << QString(NAME);
    QDBusMessage answer = _dbus.call(addMessage);
    if(answer.type() == QDBusMessage::ErrorMessage)
    {
        QString error = QString(tr("Error while adding entry: %1 - %2")).arg(answer.errorName()).arg(answer.errorMessage());
        WARNING(error);
        showError(error);
        return false;
    }
    return true;
}

QString EntryManager::getSecret(QString name)
{
    QDBusMessage askEntryMessage = QDBusMessage::createMethodCall("org.kde.kwalletd5", "/modules/kwalletd5", "org.kde.KWallet", "readMap");
    askEntryMessage << (int) _handle << QString(NAME) << name << QString(NAME);
    QDBusMessage answer = _dbus.call(askEntryMessage);
    if(answer.type() == QDBusMessage::ErrorMessage)
    {
        QString error = QString(tr("Error while getting entry: %1 - %2")).arg(answer.errorName()).arg(answer.errorMessage());
        WARNING(error);
        showError(error);
        return "";
    }

    return byteToHash(answer.arguments().at(0).toByteArray())["secret"];
}

void EntryManager::aboutQt()
{
    QMessageBox::aboutQt(nullptr);
}

void EntryManager::getDisconnectSignal()
{
    disconnectFromDbus();
    QString error = QString(tr("%1 got disconnected from KWallet.")).arg(NAME);
    CRITICAL(error);
    criticalError(error);
}

void EntryManager::getDisconnectSignal(int handle)
{
    if(handle == this->_handle)
    {
        getDisconnectSignal();
    }
}

void EntryManager::getDisconnectSignal(QString wallet, QString application)
{
    Q_UNUSED(wallet);
    if(application == NAME)
    {
        getDisconnectSignal();
    }
}

void EntryManager::showError(QString error)
{
    QMessageBox::warning(
                nullptr,
                tr("OTPwallet error"),
                error);
    return;
}

void EntryManager::criticalError(QString error)
{
    QMessageBox::critical(
                nullptr,
                tr("OTPwallet critical error"),
                error);
    QCoreApplication::exit(1);
    return;
}

void EntryManager::connectToDbus()
{
    if(_handle != 0)
    {
        WARNING(tr("Already connected"));
        return;
    }
    _dbus = QDBusConnection::connectToBus(QDBusConnection::SessionBus, QString("org.top-ranger.%1").arg(NAME));
    if(!_dbus.isConnected())
    {
        QString error = QString(tr("Can not connect to KWallet: %1 - %2")).arg(_dbus.lastError().name()).arg(_dbus.lastError().message());
        CRITICAL(error);
        criticalError(error);
        return;
    }

    QDBusMessage walletMessage = QDBusMessage::createMethodCall("org.kde.kwalletd5", "/modules/kwalletd5", "org.kde.KWallet", "wallets");
    QDBusMessage answerWallets = _dbus.call(walletMessage);
    if(answerWallets.type() == QDBusMessage::ErrorMessage)
    {
        QString error = QString(tr("Error while opening wallet: %1 - %2")).arg(answerWallets.errorName()).arg(answerWallets.errorMessage());
        CRITICAL(error);
        criticalError(error);
        return;
    }
    QStringList walletList = answerWallets.arguments().at(0).toStringList();
    if(walletList.length() == 0)
    {
        QString error = QString(tr("There are currently no wallets. Please create one first."));
        CRITICAL(error);
        criticalError(error);
        return;
    }
    else if(walletList.length() == 1)
    {
        _wallet = walletList[0];
    }
    else
    {
        DEBUG("Implement wallet selection - for now use first wallet");
        _wallet = walletList[0];
    }

    QDBusMessage openMessage = QDBusMessage::createMethodCall("org.kde.kwalletd5", "/modules/kwalletd5", "org.kde.KWallet", "open");
    openMessage << _wallet << (qlonglong) 0 << QString(NAME);
    QDBusMessage answer = _dbus.call(openMessage);
    if(answer.type() == QDBusMessage::ErrorMessage)
    {

        QString error = QString(tr("Error while opening wallet: %1 - %2")).arg(answer.errorName()).arg(answer.errorMessage());
        CRITICAL(error);
        criticalError(error);
        return;
    }
    _handle = answer.arguments().at(0).toInt();
    if(_handle == -1)
    {
        QString error = QString("Can not open wallet");
        CRITICAL(error);
        _handle = 0;
        criticalError(error);
        return;
    }
    // Signals
    _dbus.connect("org.kde.kwalletd5", "/modules/kwalletd5", "org.kde.KWallet", "applicationDisconnected", this, SLOT(getDisconnectSignal(QString,QString)));
    _dbus.connect("org.kde.kwalletd5", "/modules/kwalletd5", "org.kde.KWallet", "walletClosed", this, SLOT(getDisconnectSignal(int)));

    createFolders();
}

void EntryManager::disconnectFromDbus()
{
    if(_handle == 0)
    {
        QString debug = tr("Not connected");
        DEBUG(debug);
        return;
    }
    QDBusMessage closeMessage = QDBusMessage::createMethodCall("org.kde.kwalletd5", "/modules/kwalletd5", "org.kde.KWallet", "close");
    closeMessage << (int) _handle << false << QString(NAME);
    QDBusMessage answer = _dbus.call(closeMessage);
    if(answer.type() == QDBusMessage::ErrorMessage)
    {
        QString error = QString(tr("Error while closing wallet: %1 - %2")).arg(answer.errorName()).arg(answer.errorMessage());
        CRITICAL(error);
        criticalError(error);
        return;
    }
    _dbus.disconnectFromBus(QString("org.top-ranger.%1").arg(NAME));
    _dbus = QDBusConnection("");
    _handle = 0;
    _wallet = "";
}

void EntryManager::createFolders()
{
    QDBusMessage askFolderMessage = QDBusMessage::createMethodCall("org.kde.kwalletd5", "/modules/kwalletd5", "org.kde.KWallet", "hasFolder");
    askFolderMessage << (int) _handle << QString(NAME) << QString(NAME);
    QDBusMessage answer = _dbus.call(askFolderMessage);
    if(answer.type() == QDBusMessage::ErrorMessage)
    {
        QString error = QString(tr("Error while creating folders: %1 - %2")).arg(answer.errorName()).arg(answer.errorMessage());
        CRITICAL(error);
        criticalError(error);
        return;
    }

    if(!answer.arguments().at(0).toBool())
    {
        QDBusMessage createFolderMessage = QDBusMessage::createMethodCall("org.kde.kwalletd5", "/modules/kwalletd5", "org.kde.KWallet", "createFolder");
        createFolderMessage << (int) _handle << QString(NAME) << QString(NAME);
        answer = _dbus.call(createFolderMessage);
        if(answer.type() == QDBusMessage::ErrorMessage)
        {
            QString error = QString(tr("Error while creating folders: %1 - %2")).arg(answer.errorName()).arg(answer.errorMessage());
            CRITICAL(error);
            criticalError(error);
            return;
        }
    }
}
