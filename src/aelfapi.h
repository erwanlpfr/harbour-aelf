/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef AELFAPI_H
#define AELFAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QDate>
#include <QString>
#include <QTimer>

class Information;
class Mass;
class Reading;
class HourLiturgy;

class AELFAPI : public QObject {
    Q_OBJECT

public:
    explicit AELFAPI(QObject* parent = nullptr);
    
    void fetchInformation(const QDate& date, const QString& zone);
    void fetchMasses(const QDate& date, const QString& zone);
    void fetchHourLiturgy(const QDate& date, const QString& zone, const QString& hourType);

signals:
    void informationReady(const QDate& date, const QString& zone, Information* information);
    void massesReady(const QDate& date, const QString& zone, QList<Mass*> masses);
    void hourLiturgyReady(const QDate& date, const QString& zone, HourLiturgy* hourLiturgy);
    void errorOccurred(const QDate& date, const QString& zone, const QString& error);

private slots:
    void handleNetworkReply(QNetworkReply* reply);
    void retryFailedRequest();

private:
    struct RequestInfo {
        QString endpoint;
        QDate date;
        QString zone;
        QString requestType;
        QString hourType;
        int attemptCount;
    };
    
    QNetworkAccessManager* m_manager;
    QString m_baseUrl;
    QMap<QNetworkReply*, RequestInfo> m_pendingRequests;
    QMap<QString, RequestInfo> m_retryRequests;
    QMap<QString, QTimer*> m_retryTimers;

    QNetworkReply* makeRequest(const QString& endpoint, const QDate& date, const QString& zone, const QString& requestType, const QString& hourType = QString());
    void handleNetworkError(QNetworkReply* reply, const QString& errorMessage);
    void handleJsonError(QNetworkReply* reply, const QString& errorMessage);
    void scheduleRetry(const RequestInfo& requestInfo);
    
    Information* parseInformation(const QJsonObject& json);
    QList<Mass*> parseMasses(const QJsonObject& json);
    HourLiturgy* parseHourLiturgy(const QJsonObject& json, const QString& hourType);
    QJsonObject* extractInformations(const QJsonObject& json);
    
    QString getRequestKey(const RequestInfo& requestInfo) const;
};

#endif // AELFAPI_H
