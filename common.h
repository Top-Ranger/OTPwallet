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


#ifndef COMMON_H
#define COMMON_H

#include <QDebug>

#define DEBUG(x) qDebug() << "DEBUG in" << Q_FUNC_INFO << ":" << x
#define WARNING(x) qWarning() << "WARNING in" << Q_FUNC_INFO << ":" << x
#define CRITICAL(x) qCritical() << "CRITICAL in" << Q_FUNC_INFO << ":" << x
#define FATAL(x) qFatal("%s", QString("FATAL in %1: %2").arg(Q_FUNC_INFO).arg(x).toLatin1().data())

#endif // COMMON_H
