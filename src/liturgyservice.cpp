/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "liturgyservice.h"
#include "aelfapi.h"
#include "information.h"
#include "mass.h"
#include "hourliturgy.h"

LiturgyService::LiturgyService(QObject* parent)
    : QObject(parent)
    , m_api(new AELFAPI(this))
{
    connect(m_api, &AELFAPI::informationReady, this, &LiturgyService::onInformationReady);
    connect(m_api, &AELFAPI::massesReady, this, &LiturgyService::onMassesReady);
    connect(m_api, &AELFAPI::hourLiturgyReady, this, &LiturgyService::onHourLiturgyReady);
    connect(m_api, &AELFAPI::errorOccurred, this, &LiturgyService::onErrorOccurred);
}

void LiturgyService::fetchInformation(const QDate& date, const QString& zone) {
    m_api->fetchInformation(date, zone);
}

void LiturgyService::fetchMasses(const QDate& date, const QString& zone) {
    m_api->fetchMasses(date, zone);
}

void LiturgyService::fetchHourLiturgy(const QDate& date, const QString& zone, HourLiturgy::HourType type) {
    m_api->fetchHourLiturgy(date, zone, HourLiturgy::typeToString(type));
}

void LiturgyService::onInformationReady(const QDate& date, const QString& zone, Information* information) {
    emit informationFetched(date, zone, information);
}

void LiturgyService::onMassesReady(const QDate& date, const QString& zone, QList<Mass*> masses) {
    emit massesFetched(date, zone, masses);
}

void LiturgyService::onHourLiturgyReady(const QDate& date, const QString& zone, HourLiturgy* hourLiturgy) {
    emit hourLiturgyFetched(date, zone, hourLiturgy->hourType(), hourLiturgy);
}

void LiturgyService::onErrorOccurred(const QDate& date, const QString& zone, const QString& error) {
    emit errorOccurred(date, zone, error);
}
