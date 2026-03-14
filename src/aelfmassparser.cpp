/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "aelfmassparser.h"
#include "aelfformatter.h"
#include <QRegularExpression>

QList<Reading*> AelfMassParser::parseReadings(const QJsonArray& lectures, QObject* parent) {
    QList<Reading*> readings;
    QList<QJsonObject> gospels;

    for (const QJsonValue& lectureValue : lectures) {
        if (!lectureValue.isObject())
            continue;

        QJsonObject lecture = lectureValue.toObject();
        QString type = lecture["type"].toString();

        if (type == "evangile") {
            QJsonObject cleanedGospel = lecture;
            QString contenu = lecture["contenu"].toString();

            QRegularExpression re("\\s*<p>\\s*OU LECTURE BREVE\\s*</p>.*",
                                  QRegularExpression::CaseInsensitiveOption |
                                      QRegularExpression::DotMatchesEverythingOption);
            contenu.remove(re);

            cleanedGospel["contenu"] = contenu.trimmed();
            gospels.append(cleanedGospel);
        } else {
            Reading* reading = parseReading(lecture, parent);
            if (reading) {
                readings.append(reading);
            }
        }
    }

    if (!gospels.isEmpty()) {
        readings.append(handleGospelVariants(gospels, parent));
    }

    return readings;
}

Reading* AelfMassParser::parseReading(const QJsonObject& lecture, QObject* parent) {
    QString type = lecture["type"].toString();
    bool hasGospelVerse = !lecture["verset_evangile"].toString().isEmpty();
    Reading::ReadingType readingType = detectReadingType(type, hasGospelVerse);

    return new Reading(readingType,
                       AelfFormatter::processHtml(lecture["refrain_psalmique"].toString()),
                       lecture["titre"].toString(), QString(), QString(),
                       AelfFormatter::processHtml(lecture["contenu"].toString()),
                       lecture["ref"].toString(), lecture["intro_lue"].toString(),
                       AelfFormatter::processHtml(lecture["verset_evangile"].toString()),
                       lecture["ref_refrain"].toString(), parent);
}

Reading::ReadingType AelfMassParser::detectReadingType(const QString& type, bool hasGospelVerse) {
    if (type == "psaume")
        return Reading::Psaume;
    if (type == "cantique")
        return Reading::Cantique;
    if (type == "sequence")
        return Reading::Sequence;
    if (type == "entree_messianique")
        return Reading::EntreeMessianique;
    if (type == "evangile") {
        return hasGospelVerse ? Reading::EvangileLong : Reading::EvangileCourt;
    }

    if (type.startsWith("lecture_")) {
        bool ok;
        int num = type.mid(8).toInt(&ok);
        if (ok && num >= 1 && num <= 10) {
            return static_cast<Reading::ReadingType>(Reading::Lecture1 + num - 1);
        }
    }

    return Reading::Unknown;
}

QList<Reading*> AelfMassParser::handleGospelVariants(const QList<QJsonObject>& gospels,
                                                     QObject* parent) {
    QList<Reading*> readings;

    for (const QJsonObject& gospel : gospels) {
        Reading::ReadingType type;

        if (gospels.size() == 1) {
            type = Reading::Evangile;
        } else if (gospels.size() == 2) {
            bool hasVersetEvangile = !gospel["verset_evangile"].toString().isEmpty();
            type = hasVersetEvangile ? Reading::EvangileLong : Reading::EvangileCourt;
        } else {
            bool hasVersetEvangile = !gospel["verset_evangile"].toString().isEmpty();
            type = hasVersetEvangile ? Reading::EvangileLong : Reading::Evangile;
        }

        readings.append(
            new Reading(type, AelfFormatter::processHtml(gospel["refrain_psalmique"].toString()),
                        gospel["titre"].toString(), QString(), QString(),
                        AelfFormatter::processHtml(gospel["contenu"].toString()),
                        gospel["ref"].toString(), gospel["intro_lue"].toString(),
                        AelfFormatter::processHtml(gospel["verset_evangile"].toString()),
                        gospel["ref_verset"].toString(), parent));
    }

    return readings;
}
