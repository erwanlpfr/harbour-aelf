/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "aelfapi.h"
#include "information.h"
#include "mass.h"
#include "reading.h"
#include "hourliturgy.h"
#include "liturgicalcolorhelper.h"
#include "aelfhourliturgyparser.h"
#include "aelfmassparser.h"
#include "aelfformatter.h"
#include "errorhandler.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QDebug>

AELFAPI::AELFAPI(QObject* parent) : QObject(parent), m_manager(new QNetworkAccessManager(this)), m_baseUrl("https://api.aelf.org/v1/") {
    connect(m_manager, &QNetworkAccessManager::finished, this, &AELFAPI::handleNetworkReply);
}

QNetworkReply* AELFAPI::makeRequest(const QString& endpoint, const QDate& date, const QString& zone, const QString& requestType, const QString& hourType) {
    QString url = QString("%1%2/%3/%4").arg(m_baseUrl, endpoint, date.toString("yyyy-MM-dd"), zone);
    QNetworkRequest request(url);
    request.setRawHeader("accept", "*/*");
    QNetworkReply* reply = m_manager->get(request);
    
    RequestInfo requestInfo;
    requestInfo.endpoint = endpoint;
    requestInfo.date = date;
    requestInfo.zone = zone;
    requestInfo.requestType = requestType;
    requestInfo.hourType = hourType;
    requestInfo.attemptCount = 1;
    
    m_pendingRequests[reply] = requestInfo;
    
    reply->setProperty("requestType", requestType);
    reply->setProperty("date", date);
    reply->setProperty("zone", zone);
    if (!hourType.isEmpty()) {
        reply->setProperty("hourType", hourType);
    }
    return reply;
}

void AELFAPI::handleNetworkError(QNetworkReply* reply, const QString& errorMessage) {
    auto it = m_pendingRequests.find(reply);
    if (it == m_pendingRequests.end()) {
        reply->deleteLater();
        return;
    }
    
    RequestInfo requestInfo = it.value();
    m_pendingRequests.erase(it);
    
    ErrorHandler* errorHandler = ErrorHandler::instance();
    QString localizedError = errorHandler->getLocalizedErrorMessage(ErrorType::NetworkError, errorMessage);
    
    if (errorHandler->shouldRetry(ErrorType::NetworkError, requestInfo.attemptCount)) {
        qDebug() << "Retrying request after" << errorMessage << "- attempt" << requestInfo.attemptCount;
        scheduleRetry(requestInfo);
    } else {
        qWarning() << "Request failed permanently after" << requestInfo.attemptCount << "attempts:" << errorMessage;
        emit errorOccurred(requestInfo.date, requestInfo.zone, localizedError);
    }
    
    reply->deleteLater();
}

void AELFAPI::handleJsonError(QNetworkReply* reply, const QString& errorMessage) {
    auto it = m_pendingRequests.find(reply);
    if (it == m_pendingRequests.end()) {
        reply->deleteLater();
        return;
    }
    
    RequestInfo requestInfo = it.value();
    m_pendingRequests.erase(it);
    
    ErrorHandler* errorHandler = ErrorHandler::instance();
    QString localizedError = errorHandler->getLocalizedErrorMessage(ErrorType::ParseError, errorMessage);
    
    qWarning() << "JSON parsing error:" << errorMessage;
    emit errorOccurred(requestInfo.date, requestInfo.zone, localizedError);
    
    reply->deleteLater();
}

void AELFAPI::fetchInformation(const QDate& date, const QString& zone) {
    makeRequest("informations", date, zone, "information");
}

void AELFAPI::fetchMasses(const QDate& date, const QString& zone) {
    makeRequest("messes", date, zone, "masses");
}

void AELFAPI::fetchHourLiturgy(const QDate& date, const QString& zone, const QString& hourType) {
    makeRequest(hourType, date, zone, "hourLiturgy", hourType);
}

void AELFAPI::handleNetworkReply(QNetworkReply* reply) {
    auto it = m_pendingRequests.find(reply);
    if (it == m_pendingRequests.end()) {
        reply->deleteLater();
        return;
    }
    
    RequestInfo requestInfo = it.value();
    m_pendingRequests.erase(it);
    
    if (reply->error() != QNetworkReply::NoError) {
        handleNetworkError(reply, reply->errorString());
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    
    if (doc.isNull() || !doc.isObject()) {
        handleJsonError(reply, "Invalid JSON response");
        return;
    }

    QJsonObject json = doc.object();
    QString requestType = requestInfo.requestType;

    if (requestType == "information") {
        Information* info = parseInformation(json);
        emit informationReady(requestInfo.date, requestInfo.zone, info);
    } else if (requestType == "masses") {
        QList<Mass*> masses = parseMasses(json);
        emit massesReady(requestInfo.date, requestInfo.zone, masses);
    } else if (requestType == "hourLiturgy") {
        HourLiturgy* hourLiturgy = parseHourLiturgy(json, requestInfo.hourType);
        emit hourLiturgyReady(requestInfo.date, requestInfo.zone, hourLiturgy);
    }

    reply->deleteLater();
}

Information* AELFAPI::parseInformation(const QJsonObject& json) {
    QJsonObject* infos = extractInformations(json);
    if (!infos) return nullptr;

    return new Information(
        (*infos)["date"].toString(),
        (*infos)["zone"].toString(),
        (*infos)["couleur"].toString(),
        (*infos)["annee"].toString().toInt(),
        (*infos)["temps_liturgique"].toString(),
        (*infos)["semaine"].toInt(),
        (*infos)["jour"].toInt(),
        (*infos)["jour_liturgique_nom"].toString(),
        (*infos)["fete"].toString(),
        (*infos)["degre"].toString(),
        (*infos)["ligne1"].toString(),
        (*infos)["ligne2"].toString(),
        (*infos)["ligne3"].toString(),
        (*infos)["couleur2"].toString(),
        (*infos)["couleur3"].toString(),
        nullptr
    );
}

QList<Mass*> AELFAPI::parseMasses(const QJsonObject& json) {
    QList<Mass*> masses;
    QJsonObject* infos = extractInformations(json);
    
    if (!infos || !json.contains("messes") || !json["messes"].isArray()) {
        return masses;
    }

    QJsonArray messesArray = json["messes"].toArray();
    for (const QJsonValue& massValue : messesArray) {
        if (!massValue.isObject()) continue;
        
        QJsonObject massObject = massValue.toObject();
        QString name = AelfFormatter::capitalize(massObject["nom"].toString());
        QList<Reading*> readings;
        
        if (massObject.contains("lectures") && massObject["lectures"].isArray()) {
            readings = AelfMassParser::parseReadings(massObject["lectures"].toArray(), nullptr);
        }
        
        masses.append(new Mass(name, readings, nullptr));
    }
    
    return masses;
}

HourLiturgy* AELFAPI::parseHourLiturgy(const QJsonObject& json, const QString& hourType) {
    HourLiturgy::HourType type = HourLiturgy::Vespers;
    
    if (hourType == "complies") type = HourLiturgy::Compline;
    else if (hourType == "laudes") type = HourLiturgy::Lauds;
    else if (hourType == "lectures") type = HourLiturgy::Lectures;
    else if (hourType == "none") type = HourLiturgy::None;
    else if (hourType == "sexte") type = HourLiturgy::Sext;
    else if (hourType == "tierce") type = HourLiturgy::Terce;
    else if (hourType == "vepres") type = HourLiturgy::Vespers;
    
    QList<Reading*> readings = AelfHourLiturgyParser::parse(json, hourType, nullptr);
    return new HourLiturgy(type, readings, nullptr);
}

QJsonObject* AELFAPI::extractInformations(const QJsonObject& json) {
    if (!json.contains("informations") || !json["informations"].isObject()) {
        return nullptr;
    }
    
    return new QJsonObject(json["informations"].toObject());
}

QString AELFAPI::getRequestKey(const RequestInfo& requestInfo) const {
    return QString("%1_%2_%3_%4").arg(requestInfo.requestType, requestInfo.date.toString("yyyy-MM-dd"), 
                                     requestInfo.zone, requestInfo.hourType);
}

void AELFAPI::scheduleRetry(const RequestInfo& requestInfo) {
    ErrorHandler* errorHandler = ErrorHandler::instance();
    int retryDelay = errorHandler->getRetryDelay(ErrorType::NetworkError, requestInfo.attemptCount);
    
    RequestInfo retryInfo = requestInfo;
    retryInfo.attemptCount++;
    
    QString requestKey = getRequestKey(retryInfo);
    m_retryRequests[requestKey] = retryInfo;
    
    QTimer* timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(retryDelay);
    
    m_retryTimers[requestKey] = timer;
    
    connect(timer, &QTimer::timeout, this, &AELFAPI::retryFailedRequest);
    timer->start();
    
    qDebug() << "Scheduled retry in" << retryDelay << "ms for request" << requestKey;
}

void AELFAPI::retryFailedRequest() {
    QTimer* timer = qobject_cast<QTimer*>(sender());
    if (!timer) return;
    
    QString requestKey;
    for (auto it = m_retryTimers.begin(); it != m_retryTimers.end(); ++it) {
        if (it.value() == timer) {
            requestKey = it.key();
            break;
        }
    }
    
    if (requestKey.isEmpty()) {
        timer->deleteLater();
        return;
    }
    
    auto retryIt = m_retryRequests.find(requestKey);
    if (retryIt == m_retryRequests.end()) {
        m_retryTimers.remove(requestKey);
        timer->deleteLater();
        return;
    }
    
    RequestInfo requestInfo = retryIt.value();
    m_retryRequests.erase(retryIt);
    m_retryTimers.remove(requestKey);
    
    qDebug() << "Retrying request" << getRequestKey(requestInfo) << "- attempt" << requestInfo.attemptCount;
    
    makeRequest(requestInfo.endpoint, requestInfo.date, requestInfo.zone, 
               requestInfo.requestType, requestInfo.hourType);
    
    timer->deleteLater();
}
