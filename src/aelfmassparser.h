/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef AELFMASSPARSER_H
#define AELFMASSPARSER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include "reading.h"

class AelfMassParser {
public:
    static QList<Reading*> parseReadings(const QJsonArray& lectures, QObject* parent = nullptr);

private:
    static Reading* parseReading(const QJsonObject& lecture, QObject* parent);
    static Reading::ReadingType detectReadingType(const QString& type, bool hasGospelVerse);
    static QList<Reading*> handleGospelVariants(const QList<QJsonObject>& gospels, QObject* parent);
};

#endif // AELFMASSPARSER_H
