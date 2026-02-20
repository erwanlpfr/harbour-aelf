/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "informationmodel.h"
#include "information.h"
#include "liturgyrepository.h"
#include "liturgyidentifierkey.h"

InformationModel::InformationModel(QObject* parent)
    : LiturgyBaseModel(parent)
    , m_information(nullptr)
{
    connect(m_liturgyRepository, &LiturgyRepository::informationChanged, this, &InformationModel::onInformationChanged);
}

Information* InformationModel::information() const
{
    return m_information;
}

void InformationModel::onInformationChanged(const LiturgyIdentifierKey& key, Information* information)
{
    if (LiturgyIdentifierKeyFactory::getPair(m_date, m_zone) == key) {
        m_information = information;
        emit informationChanged();
        setDataLoaded(information == nullptr);
    }
}

void InformationModel::loadData()
{
    m_liturgyRepository->loadInformation(LiturgyIdentifierKeyFactory::getPair(m_date, m_zone));
}