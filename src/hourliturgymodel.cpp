/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "hourliturgymodel.h"
#include "liturgyrepository.h"
#include "liturgyidentifierkey.h"
#include "readingtabmodel.h"

HourLiturgyModel::HourLiturgyModel(QObject* parent)
    : InformationModel(parent)
    , m_type(HourLiturgy::Vespers)
    , m_hourLiturgy(nullptr)
{
    connect(m_liturgyRepository, &LiturgyRepository::hourLiturgyChanged, this, &HourLiturgyModel::onHourLiturgyChanged);
}

HourLiturgy::HourType HourLiturgyModel::type() const
{
    return m_type;
}

void HourLiturgyModel::setType(HourLiturgy::HourType type)
{
    if (m_type != type) {
        m_type = type;
        emit typeChanged();
        if (m_date.isValid() && !m_zone.isEmpty()) {
            setLoading(true);
            m_liturgyRepository->loadHourLiturgy(LiturgyIdentifierKeyFactory::getPair(m_date, m_zone), m_type);
        }
    }
}

HourLiturgy* HourLiturgyModel::hourLiturgy() const
{
    return m_hourLiturgy;
}

void HourLiturgyModel::onHourLiturgyChanged(const LiturgyIdentifierKey& key, HourLiturgy::HourType type, HourLiturgy* hourLiturgy)
{
    if (LiturgyIdentifierKeyFactory::getPair(m_date, m_zone) == key && m_type == type) {
        m_hourLiturgy = hourLiturgy;
        emit hourLiturgyChanged();
        setDataLoaded(hourLiturgy == nullptr || hourLiturgy->readingsModel()->readings().isEmpty());
    }
}

void HourLiturgyModel::loadData()
{
    m_liturgyRepository->loadHourLiturgy(LiturgyIdentifierKeyFactory::getPair(m_date, m_zone), m_type);
}
