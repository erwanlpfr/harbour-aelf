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
    QString subtitle = AelfFormatter::addAntienneBefore(antienne);
    QString ref = inv["reference"].toString();
    QString content = AelfFormatter::processHtml(inv["texte"].toString() + HtmlUtils::p(AelfTexts::gloriaPatri()));
    
    return new Reading(
        Reading::PsaumeInvitatoire,
        subtitle,
        QCoreApplication::translate("AelfHourLiturgyParser", "Antienne invitatoire"),
        QString(),
        QString(),
        content,
        ref.isEmpty() ? QString() : "Ps " + ref,
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
        QCoreApplication::translate("AelfHourLiturgyParser", "Hymne"),
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
        QCoreApplication::translate("AelfHourLiturgyParser", "Verset"),
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

QList<Reading*> AelfHourLiturgyParser::parsePsalmsAndCantiques(const QJsonObject& hour, QObject* parent)
{
    QList<Reading*> readings;
    
    for (int i = 1; i <= 5; ++i) {
        QString psaumeKey = QString("psaume_%1").arg(i);
        QString cantiqueKey = QString("cantique_%1").arg(i);
        
        if (hour.contains(psaumeKey) && hour[psaumeKey].isObject()) {
            QJsonObject psaume = hour[psaumeKey].toObject();
            QString ref = psaume["reference"].toString();
            QString title = ref;
            QString antienne = findAntienne(hour, i);
            
            if (antienne.isEmpty()) {
                antienne = findPreviousAntienne(hour, i, title);
            }
            
            QString subtitle = AelfFormatter::addAntienneBefore(antienne);
            QString content = AelfFormatter::processHtml(psaume["texte"].toString() + HtmlUtils::p(AelfTexts::gloriaPatri()));
            
            bool isCanticle = ref.toLower().contains("cantique");
            Reading::ReadingType type = isCanticle ? Reading::Canticle : Reading::Psalm;
            
            QString displayRef;
            QString displayTitle;
            
            if (isCanticle) {
                QStringList parts = ref.split("(");
                if (parts.length() > 0) {
                    displayTitle = AelfFormatter::capitalize(parts[0].trimmed());
                }
                if (parts.length() > 1) {
                    QRegularExpression parenRe("[\\(\\)\\.]");
                    displayRef = parts[1].remove(parenRe).trimmed();
                }
            } else {
              displayTitle = ref.isEmpty() ? QString() : "Psaume " + ref;
              displayRef = ref.isEmpty() ? QString() : "Ps " + ref;
            }

            readings.append(new Reading(
                type, subtitle, displayTitle, QString(), QString(), content,
                displayRef, QString(), QString(), QString(), parent));
        }
        
        if (hour.contains(cantiqueKey) && hour[cantiqueKey].isObject()) {
            QJsonObject cantique = hour[cantiqueKey].toObject();
            QString antienne = findAntienne(hour, i);
            QString subtitle = AelfFormatter::addAntienneBefore(antienne);
            QString content = AelfFormatter::processHtml(cantique["texte"].toString() + HtmlUtils::p(AelfTexts::gloriaPatri()));
            
            readings.append(new Reading(
                Reading::Canticle,
                subtitle,
                cantique["titre"].toString(),
                QString(),
                QString(),
                content,
                cantique["reference"].toString(),
                QString(),
                QString(),
                QString(),
                parent
            ));
        }
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
        QCoreApplication::translate("AelfHourLiturgyParser", "Parole de Dieu"),
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
    
    QString subtitle = AelfFormatter::addAntienneBefore(antienne);
    QString content = AelfFormatter::processHtml(cantique["texte"].toString() + HtmlUtils::p(AelfTexts::gloriaPatri()));
    
    return new Reading(
        Reading::CantiqueMariale,
        subtitle,
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
        title = QCoreApplication::translate("AelfHourLiturgyParser", "Intercession");
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
        QCoreApplication::translate("AelfHourLiturgyParser", "Notre Père"),
        QString(),
        QString(),
        AelfTexts::notrePereText(),
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
        QCoreApplication::translate("AelfHourLiturgyParser", "Oraison et bénédiction"),
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

QString AelfHourLiturgyParser::findPreviousAntienne(const QJsonObject& hour, int startIndex, const QString& title)
{
    QRegularExpression splitRe("- (I|V)", QRegularExpression::CaseInsensitiveOption);
    if (!splitRe.match(title).hasMatch()) {
        return QString();
    }
    
    for (int i = startIndex - 1; i > 0; --i) {
        QString antienne = findAntienne(hour, i);
        if (!antienne.isEmpty()) {
            return antienne;
        }
    }
    
    return QString();
}
