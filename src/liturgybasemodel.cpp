/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "liturgybasemodel.h"
#include "liturgyidentifierkey.h"
#include "liturgyrepository.h"

LiturgyBaseModel::LiturgyBaseModel(QObject* parent)
    : QObject(parent), m_liturgyRepository(LiturgyRepository::instance()), m_date(), m_zone(),
      m_loading(false), m_error(), m_empty(true) {
    connect(m_liturgyRepository, &LiturgyRepository::errorOccurred, this,
            [this](const LiturgyIdentifierKey& key, const QString& error) {
                if (LiturgyIdentifierKeyFactory::getPair(m_date, m_zone) == key) {
                    setError(error);
                }
            });

    connect(this, &LiturgyBaseModel::dateChanged, this, [this]() {
        if (m_date.isValid() && !m_zone.isEmpty()) {
            setLoading(true);
            loadData();
        }
    });

    connect(this, &LiturgyBaseModel::zoneChanged, this, [this]() {
        if (m_date.isValid() && !m_zone.isEmpty()) {
            setLoading(true);
            loadData();
        }
    });
}

QDate LiturgyBaseModel::date() const {
    return m_date;
}

void LiturgyBaseModel::setDate(const QDate& date) {
    if (m_date != date) {
        m_date = date;
        emit dateChanged();
    }
}

QString LiturgyBaseModel::zone() const {
    return m_zone;
}

void LiturgyBaseModel::setZone(const QString& zone) {
    if (m_zone != zone) {
        m_zone = zone;
        emit zoneChanged();
    }
}

bool LiturgyBaseModel::loading() const {
    return m_loading;
}

void LiturgyBaseModel::setLoading(bool loading) {
    if (m_loading != loading) {
        m_loading = loading;
        emit loadingChanged();
        setEmpty(loading ? false : m_empty);
    }
}

QString LiturgyBaseModel::error() const {
    return m_error;
}

void LiturgyBaseModel::setError(const QString& error) {
    if (m_error != error) {
        m_error = error;
        emit errorChanged();
    }
}

bool LiturgyBaseModel::empty() const {
    return m_empty;
}

void LiturgyBaseModel::setEmpty(bool empty) {
    if (m_empty != empty) {
        m_empty = empty;
        emit emptyChanged();
    }
}

void LiturgyBaseModel::setDataLoaded(bool empty) {
    setEmpty(empty);
    setLoading(false);
    setError(QString());
}