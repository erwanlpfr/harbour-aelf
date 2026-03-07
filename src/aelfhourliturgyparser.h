/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef AELFHOURLITURGYPARSER_H
#define AELFHOURLITURGYPARSER_H

#include <QJsonObject>
#include <QList>
#include "reading.h"

class AelfHourLiturgyParser {
public:
    static QList<Reading*> parse(const QJsonObject& json, const QString& hourType, QObject* parent = nullptr);

private:
    static Reading* parseIntroduction(const QJsonObject& hour, QObject* parent);
    static Reading* parsePsaumeInvitatoire(const QJsonObject& hour, QObject* parent);
    static Reading* parseHymne(const QJsonObject& hour, QObject* parent);
    static Reading* parseVersetPsaume(const QJsonObject& hour, QObject* parent);
    static QList<Reading*> parsePsalmsAndCantiques(const QJsonObject& hour, QObject* parent);
    static Reading* parsePericope(const QJsonObject& hour, QObject* parent);
    static Reading* parseLecture(const QJsonObject& hour, QObject* parent);
    static Reading* parseTextePatristique(const QJsonObject& hour, QObject* parent);
    static Reading* parseCantiqueMariale(const QJsonObject& hour, QObject* parent);
    static Reading* parseTeDeum(const QJsonObject& hour, QObject* parent);
    static Reading* parseIntercession(const QJsonObject& hour, QObject* parent);
    static Reading* parseNotrePere(const QJsonObject& hour, QObject* parent);
    static Reading* parseOraison(const QJsonObject& hour, QObject* parent);
    
    static QString findAntienne(const QJsonObject& hour, int index);
};

#endif // AELFHOURLITURGYPARSER_H
