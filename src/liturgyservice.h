/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef LITURGYSERVICE_H
#define LITURGYSERVICE_H

#include <QDate>
#include <QList>
#include <QObject>
#include <QString>
#include "hourliturgy.h"

class AELFAPI;
class Information;
class Mass;
class HourLiturgy;

class LiturgyService : public QObject {
    Q_OBJECT

public:
    explicit LiturgyService(QObject* parent = nullptr);

    void fetchInformation(const QDate& date, const QString& zone);
    void fetchMasses(const QDate& date, const QString& zone);
    void fetchHourLiturgy(const QDate& date, const QString& zone, HourLiturgy::HourType type);

signals:
    void informationFetched(const QDate& date, const QString& zone, Information* information);
    void massesFetched(const QDate& date, const QString& zone, QList<Mass*> masses);
    void hourLiturgyFetched(const QDate& date, const QString& zone, HourLiturgy::HourType type, HourLiturgy* hourLiturgy);
    void errorOccurred(const QDate& date, const QString& zone, const QString& error);

private slots:
    void onInformationReady(const QDate& date, const QString& zone, Information* information);
    void onMassesReady(const QDate& date, const QString& zone, QList<Mass*> masses);
    void onHourLiturgyReady(const QDate& date, const QString& zone, HourLiturgy* hourLiturgy);
    void onErrorOccurred(const QDate& date, const QString& zone, const QString& error);

private:
    AELFAPI* m_api;
};

#endif // LITURGYSERVICE_H
