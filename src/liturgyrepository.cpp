/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "liturgyrepository.h"
#include "information.h"
#include "liturgyservice.h"
#include "mass.h"
#include "hourliturgy.h"
#include "liturgyidentifierkey.h"

LiturgyRepository* LiturgyRepository::s_instance = nullptr;

LiturgyRepository::LiturgyRepository(QObject* parent)
    : QObject(parent)
    , m_service(new LiturgyService(this))
{
    connect(m_service, &LiturgyService::errorOccurred,
        this, &LiturgyRepository::onServiceErrorOccurred);

    connect(m_service, &LiturgyService::informationFetched,
        this, &LiturgyRepository::onServiceInformationFetched);

    connect(m_service, &LiturgyService::massesFetched,
        this, &LiturgyRepository::onServiceMassesFetched);

    connect(m_service, &LiturgyService::hourLiturgyFetched,
        this, &LiturgyRepository::onServiceHourLiturgyFetched);
}

LiturgyRepository* LiturgyRepository::instance(QObject* parent)
{
    if (!s_instance) {
        s_instance = new LiturgyRepository(parent);
    }
    return s_instance;
}

LiturgyRepository::~LiturgyRepository()
{
    qDeleteAll(m_informationMap);
    for (auto& masses : m_massesMap) {
        qDeleteAll(masses);
    }
    qDeleteAll(m_hourLiturgyMap);
}

LiturgyIdentifierKey LiturgyRepository::createKey(const QDate& date, const QString& zone) const
{
    return qMakePair(date, zone);
}

void LiturgyRepository::loadInformation(const LiturgyIdentifierKey& key)
{
    auto information = m_informationMap.find(key);

    if (information == m_informationMap.end()) {
        m_service->fetchInformation(key.first, key.second);
    } else {
        emit informationChanged(key, information.value());
    }
}

void LiturgyRepository::loadMasses(const LiturgyIdentifierKey& key)
{
    auto information = m_informationMap.find(key);
    auto masses = m_massesMap.find(key);

    if (masses == m_massesMap.end() || information == m_informationMap.end()) {
        m_service->fetchMasses(key.first, key.second);
    } else {
        emit informationChanged(key, information.value());
        emit massesChanged(key, masses.value());
    }
}

void LiturgyRepository::onInformationFetched(const LiturgyIdentifierKey& key, Information* information) {
    m_informationMap.insert(key, information);
    emit informationChanged(key, information);
}

void LiturgyRepository::onMassesFetched(const LiturgyIdentifierKey& key, QList<Mass*> masses) {
    m_massesMap.insert(key, masses);
    emit massesChanged(key, masses);
}

void LiturgyRepository::loadHourLiturgy(const LiturgyIdentifierKey& key, HourLiturgy::HourType type) {
    HourLiturgyKey cacheKey = LiturgyIdentifierKeyFactory::getHourLiturgyKey(key, type);
    auto hourLiturgy = m_hourLiturgyMap.find(cacheKey);

    if (hourLiturgy == m_hourLiturgyMap.end()) {
        m_service->fetchHourLiturgy(key.first, key.second, type);
    } else {
        emit hourLiturgyChanged(key, type, hourLiturgy.value());
    }
}

void LiturgyRepository::onHourLiturgyFetched(const LiturgyIdentifierKey& key, HourLiturgy::HourType type, HourLiturgy* hourLiturgy) {
    HourLiturgyKey cacheKey = LiturgyIdentifierKeyFactory::getHourLiturgyKey(key, type);
    m_hourLiturgyMap.insert(cacheKey, hourLiturgy);
    emit hourLiturgyChanged(key, type, hourLiturgy);
}

void LiturgyRepository::onErrorOccurred(const LiturgyIdentifierKey& key, const QString& error) {
    emit errorOccurred(key, error);
}

void LiturgyRepository::onServiceInformationFetched(const QDate& date, const QString& zone, Information* information) {
    onInformationFetched(createKey(date, zone), information);
}

void LiturgyRepository::onServiceMassesFetched(const QDate& date, const QString& zone, QList<Mass*> masses) {
    onMassesFetched(createKey(date, zone), masses);
}

void LiturgyRepository::onServiceHourLiturgyFetched(const QDate& date, const QString& zone, HourLiturgy::HourType type, HourLiturgy* hourLiturgy) {
    onHourLiturgyFetched(createKey(date, zone), type, hourLiturgy);
}

void LiturgyRepository::onServiceErrorOccurred(const QDate& date, const QString& zone, const QString& error) {
    onErrorOccurred(createKey(date, zone), error);
}
