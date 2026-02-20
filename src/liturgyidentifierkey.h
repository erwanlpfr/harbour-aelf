/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef LITURGYIDENTIFIERKEY_H
#define LITURGYIDENTIFIERKEY_H

#include <QDate>
#include <QString>
#include "hourliturgy.h"

using LiturgyIdentifierKey = QPair<QDate, QString>;
using HourLiturgyKey = QPair<LiturgyIdentifierKey, HourLiturgy::HourType>;

class LiturgyIdentifierKeyFactory
{
public:
    static LiturgyIdentifierKey getPair(const QDate& date, const QString& zone)
    {
        return qMakePair(date, zone);
    }

    static HourLiturgyKey getHourLiturgyKey(const QDate& date, const QString& zone, HourLiturgy::HourType type)
    {
        return qMakePair(getPair(date, zone), type);
    }

    static HourLiturgyKey getHourLiturgyKey(const LiturgyIdentifierKey& key, HourLiturgy::HourType type)
    {
        return qMakePair(key, type);
    }
};

#endif // LITURGYIDENTIFIERKEY_H
