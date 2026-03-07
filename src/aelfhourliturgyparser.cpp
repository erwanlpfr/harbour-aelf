/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "aelfhourliturgyparser.h"
#include "aelfformatter.h"
#include <QJsonArray>
#include <QRegularExpression>
#include <QCoreApplication>

QList<Reading*> AelfHourLiturgyParser::parse(const QJsonObject& json, const QString& hourType, QObject* parent)
{
    QList<Reading*> readings;
    
    if (!json.contains(hourType) || !json[hourType].isObject()) {
        return readings;
    }
    
    QJsonObject hour = json[hourType].toObject();
    if (hour.contains("introduction") && !hour["introduction"].toString().isEmpty()) {
        Reading* r = parseIntroduction(hour, parent);
        if (r) readings.append(r);
    }
    if (hour.contains("psaume_invitatoire") && hour["psaume_invitatoire"].isObject()) {
        Reading* r = parsePsaumeInvitatoire(hour, parent);
        if (r) readings.append(r);
    }
    if (hour.contains("hymne") && hour["hymne"].isObject()) {
        Reading* r = parseHymne(hour, parent);
        if (r) readings.append(r);
    }
    if (hour.contains("verset_psaume") && !hour["verset_psaume"].toString().isEmpty()) {
        Reading* r = parseVersetPsaume(hour, parent);
        if (r) readings.append(r);
    }
    readings.append(parsePsalmsAndCantiques(hour, parent));
    if (hour.contains("pericope") && hour["pericope"].isObject()) {
        Reading* r = parsePericope(hour, parent);
        if (r) readings.append(r);
    }
    if (hour.contains("lecture") && hour["lecture"].isObject()) {
        Reading* r = parseLecture(hour, parent);
        if (r) readings.append(r);
    }
    if (hour.contains("texte_patristique") && !hour["texte_patristique"].toString().isEmpty()) {
        Reading* r = parseTextePatristique(hour, parent);
        if (r) readings.append(r);
    }
    if (hour.contains("te_deum") && hour["te_deum"].isObject()) {
        Reading* r = parseTeDeum(hour, parent);
        if (r) readings.append(r);
    }
    if (hour.contains("cantique_mariale") && hour["cantique_mariale"].isObject()) {
        Reading* r = parseCantiqueMariale(hour, parent);
        if (r) readings.append(r);
    }
    if (hour.contains("intercession") && !hour["intercession"].toString().isEmpty()) {
        Reading* r = parseIntercession(hour, parent);
        if (r) readings.append(r);
    }
    if (hour.contains("notre_pere")) {
        Reading* r = parseNotrePere(hour, parent);
        if (r) readings.append(r);
    }
    if (hour.contains("oraison") && !hour["oraison"].toString().isEmpty()) {
        Reading* r = parseOraison(hour, parent);
        if (r) readings.append(r);
    }
    if (hour.contains("hymne_mariale") && hour["hymne_mariale"].isObject()) {
        Reading* r = parseCantiqueMariale(hour, parent);
        if (r) readings.append(r);
    }
    
    return readings;
}

Reading* AelfHourLiturgyParser::parseIntroduction(const QJsonObject& hour, QObject* parent)
{
    QString title = hour["titre_office"].toString();
    if (title.isEmpty()) {
        title = QObject::tr("Introduction");
    }
    
    return new Reading(
        Reading::Introduction,
        QString(),
        title,
        QString(),
        QString(),
        AelfFormatter::processHtml(hour["introduction"].toString()),
        QString(),
        QString(),
        QString(),
        QString(),
        parent
    );
}

Reading* AelfHourLiturgyParser::parsePsaumeInvitatoire(const QJsonObject& hour, QObject* parent)
{
    QJsonObject inv = hour["psaume_invitatoire"].toObject();
    QString antienne = hour.value("antienne_invitatoire").toString();
    QString refrainPsalm = AelfFormatter::formatAntienne(antienne, AntiennePosition::Before);
    QString reference = inv["reference"].toString();
    QString content = AelfFormatter::processHtml(inv["texte"].toString() + HtmlUtils::p(AelfTexts::gloriaPatri()))
        + AelfFormatter::formatAntienne(antienne, AntiennePosition::After);

    return new Reading(
        Reading::PsaumeInvitatoire,
        refrainPsalm,
        QCoreApplication::translate("AelfTexts", "Antienne invitatoire"),
        QString(),
        QString(),
        content,
        reference.isEmpty() ? QString() : "Ps " + reference,
        QString(),
        QString(),
        QString(),
        parent
    );
}

Reading* AelfHourLiturgyParser::parseHymne(const QJsonObject& hour, QObject* parent)
{
    QJsonObject hymne = hour["hymne"].toObject();
    
    return new Reading(
        Reading::Hymne,
        hymne["titre"].toString(),
        QCoreApplication::translate("AelfTexts", "Hymne"),
        hymne["editeur"].toString(),
        hymne["auteur"].toString(),
        AelfFormatter::processHtml(hymne["texte"].toString()),
        QString(),
        QString(),
        QString(),
        QString(),
        parent
    );
}

Reading* AelfHourLiturgyParser::parseVersetPsaume(const QJsonObject& hour, QObject* parent)
{
    QString content = AelfFormatter::processHtml(hour["verset_psaume"].toString());
    
    return new Reading(
        Reading::VersetPsaume,
        QString(),
        QCoreApplication::translate("AelfTexts", "Verset"),
        QString(),
        QString(),
        content,
        QString(),
        QString(),
        QString(),
        QString(),
        parent
    );
}

struct PsalmData {
    Reading::ReadingType readingType;
    QString antienne;
    QString title;
    QString reference;
    QString content;
};

QList<Reading*> AelfHourLiturgyParser::parsePsalmsAndCantiques(const QJsonObject& hour, QObject* parent)
{
    QList<PsalmData> psalms;
    QString lastAntienne;

    // Pass 1: collect psalm data
    for (int i = 1; i <= 5; ++i) {
        QString psaumeKey = QString("psaume_%1").arg(i);
        QString cantiqueKey = QString("cantique_%1").arg(i);

        if (hour.contains(psaumeKey) && hour[psaumeKey].isObject()) {
            QJsonObject psaume = hour[psaumeKey].toObject();
            QString ref = psaume["reference"].toString();
            QString antienne = findAntienne(hour, i);

            if (antienne.isEmpty()) {
                antienne = lastAntienne;
            } else {
                lastAntienne = antienne;
            }

            QString content = AelfFormatter::processHtml(psaume["texte"].toString() + HtmlUtils::p(AelfTexts::gloriaPatri()));

            bool isCanticle = ref.toLower().contains("cantique");
            Reading::ReadingType readingType = isCanticle ? Reading::Canticle : Reading::Psalm;

            QString reference;
            QString title;

            if (isCanticle) {
                QStringList parts = ref.split("(");
                if (parts.length() > 0) {
                    title = AelfFormatter::capitalize(parts[0].trimmed());
                }
                if (parts.length() > 1) {
                    QRegularExpression parenRe("[\\(\\)\\.]");
                    reference = parts[1].remove(parenRe).trimmed();
                }
            } else {
                title = ref.isEmpty() ? QString() : "Psaume " + ref;
                reference = ref.isEmpty() ? QString() : "Ps " + ref;
            }

            psalms.append({readingType, antienne, title, reference, content});
        }

        if (hour.contains(cantiqueKey) && hour[cantiqueKey].isObject()) {
            QJsonObject cantique = hour[cantiqueKey].toObject();
            QString antienne = findAntienne(hour, i);
            if (antienne.isEmpty()) {
                antienne = lastAntienne;
            } else {
                lastAntienne = antienne;
            }
            QString content = AelfFormatter::processHtml(cantique["texte"].toString() + HtmlUtils::p(AelfTexts::gloriaPatri()));

            psalms.append({Reading::Canticle, antienne,
                           cantique["titre"].toString(), cantique["reference"].toString(), content});
        }
    }

    // Pass 2: place antienne before first and after last of each group
    QList<Reading*> readings;
    for (int i = 0; i < psalms.size(); ++i) {
        const auto& pd = psalms[i];
        bool isFirst = (i == 0) || (pd.antienne != psalms[i - 1].antienne);
        bool isLast = (i == psalms.size() - 1) || (pd.antienne != psalms[i + 1].antienne);

        QString refrainPsalm = isFirst ? AelfFormatter::formatAntienne(pd.antienne, AntiennePosition::Before) : QString();
        QString content = isLast ? pd.content + AelfFormatter::formatAntienne(pd.antienne, AntiennePosition::After) : pd.content;

        readings.append(new Reading(
            pd.readingType, refrainPsalm, pd.title, QString(), QString(), content,
            pd.reference, QString(), QString(), QString(), parent));
    }

    return readings;
}

Reading* AelfHourLiturgyParser::parsePericope(const QJsonObject& hour, QObject* parent)
{
    QJsonObject pericope = hour["pericope"].toObject();
    QString content = AelfFormatter::appendReponsIfPresent(pericope["texte"].toString(), hour, "repons");
    content = AelfFormatter::processHtml(content);
    
    return new Reading(
        Reading::Pericope,
        QString(),
        AelfTexts::paroleDeDieu(),
        QString(),
        QString(),
        content,
        pericope["reference"].toString(),
        QString(),
        QString(),
        QString(),
        parent
    );
}

Reading* AelfHourLiturgyParser::parseLecture(const QJsonObject& hour, QObject* parent)
{
    QJsonObject lecture = hour["lecture"].toObject();
    QString title = "« " + AelfFormatter::capitalize(lecture["titre"].toString()) + " »";
    QString content = AelfFormatter::appendReponsIfPresent(lecture["texte"].toString(), hour, "repons_lecture");
    content = AelfFormatter::processHtml(content);
    
    return new Reading(
        Reading::Lecture,
        QString(),
        title,
        QString(),
        QString(),
        content,
        lecture["reference"].toString(),
        QString(),
        QString(),
        QString(),
        parent
    );
}

Reading* AelfHourLiturgyParser::parseTextePatristique(const QJsonObject& hour, QObject* parent)
{
    QString titrePatristique = hour.value("titre_patristique").toString();
    QString title = "« " + AelfFormatter::capitalize(titrePatristique) + " »";
    QString content = AelfFormatter::appendReponsIfPresent(hour["texte_patristique"].toString(), hour, "repons_patristique");
    content = AelfFormatter::processHtml(content);
    
    QString ref;
    if (hour["texte_patristique"].isObject()) {
        ref = hour["texte_patristique"].toObject()["reference"].toString();
    }
    
    return new Reading(
        Reading::TextePatristique,
        QString(),
        title,
        QString(),
        QString(),
        content,
        ref,
        QString(),
        QString(),
        QString(),
        parent
    );
}

Reading* AelfHourLiturgyParser::parseTeDeum(const QJsonObject& hour, QObject* parent)
{
    QJsonObject teDeum = hour["te_deum"].toObject();
    
    return new Reading(
        Reading::TeDeum,
        QString(),
        teDeum["titre"].toString(),
        QString(),
        QString(),
        AelfFormatter::processHtml(teDeum["texte"].toString()),
        teDeum["reference"].toString(),
        QString(),
        QString(),
        QString(),
        parent
    );
}

Reading* AelfHourLiturgyParser::parseCantiqueMariale(const QJsonObject& hour, QObject* parent)
{
    QJsonObject cantique = hour.contains("hymne_mariale") 
        ? hour["hymne_mariale"].toObject() 
        : hour["cantique_mariale"].toObject();
    
    QString antienne;
    if (hour.contains("antienne_magnificat")) {
        antienne = hour["antienne_magnificat"].toString();
    } else if (hour.contains("antienne_benedictus")) {
        antienne = hour["antienne_benedictus"].toString();
    }
    
    QString refrainPsalm = AelfFormatter::formatAntienne(antienne, AntiennePosition::Before);
    QString content = AelfFormatter::processHtml(cantique["texte"].toString() + HtmlUtils::p(AelfTexts::gloriaPatri()))
        + AelfFormatter::formatAntienne(antienne, AntiennePosition::After);

    return new Reading(
        Reading::CantiqueMariale,
        refrainPsalm,
        cantique["titre"].toString(),
        QString(),
        QString(),
        content,
        cantique["reference"].toString(),
        QString(),
        QString(),
        QString(),
        parent
    );
}

Reading* AelfHourLiturgyParser::parseIntercession(const QJsonObject& hour, QObject* parent)
{
    QString title = hour["titre_intercession"].toString();
    if (title.isEmpty()) {
        title = AelfTexts::intercession();
    }
    return new Reading(
        Reading::Intercession,
        QString(),
        title,
        QString(),
        QString(),
        AelfFormatter::processHtml(hour["intercession"].toString()),
        QString(),
        QString(),
        QString(),
        QString(),
        parent
    );
}

Reading* AelfHourLiturgyParser::parseNotrePere(const QJsonObject& hour, QObject* parent)
{
    Q_UNUSED(hour)
    
    return new Reading(
        Reading::NotrePere,
        QString(),
        AelfTexts::notrePereLabel(),
        QString(),
        QString(),
        AelfTexts::notrePere(),
        QString(),
        QString(),
        QString(),
        QString(),
        parent
    );
}

Reading* AelfHourLiturgyParser::parseOraison(const QJsonObject& hour, QObject* parent)
{
    QString content = AelfFormatter::processHtml(hour["oraison"].toString()) + HtmlUtils::spacer() + AelfTexts::oraisonSuffix();
    
    return new Reading(
        Reading::Oraison,
        QString(),
        AelfTexts::oraisonLabel(),
        QString(),
        QString(),
        content,
        QString(),
        QString(),
        QString(),
        QString(),
        parent
    );
}

QString AelfHourLiturgyParser::findAntienne(const QJsonObject& hour, int index)
{
    QString key = QString("antienne_%1").arg(index);
    return hour.value(key).toString();
}


