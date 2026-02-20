/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "massmodel.h"
#include "liturgyrepository.h"
#include "liturgyidentifierkey.h"

MassModel::MassModel(QObject* parent)
    : InformationModel(parent), m_currentMassIndex(0)
{
    connect(m_liturgyRepository, &LiturgyRepository::massesChanged, this, &MassModel::onMassesChanged);
}

QStringList MassModel::massNames() const
{
    QStringList names;
    for (Mass* mass : m_masses) {
        names.append(mass->name());
    }
    return names;
}

Mass* MassModel::currentMass() const
{
    if (m_currentMassIndex >= 0 && m_currentMassIndex < m_masses.count()) {
        return m_masses[m_currentMassIndex];
    }
    return nullptr;
}

int MassModel::currentMassIndex() const
{
    return m_currentMassIndex;
}

void MassModel::setCurrentMassIndex(int index)
{
    if (m_currentMassIndex != index) {
        m_currentMassIndex = index;
        emit currentMassIndexChanged();
        emit currentMassChanged();
    }
}

void MassModel::onMassesChanged(const LiturgyIdentifierKey& key, QList<Mass*> masses)
{
    if (LiturgyIdentifierKeyFactory::getPair(m_date, m_zone) == key) {
        m_masses = masses;
        
        if (m_currentMassIndex >= masses.count()) {
            m_currentMassIndex = 0;
            emit currentMassIndexChanged();
        }
        
        emit massNamesChanged();
        emit currentMassChanged();
        setDataLoaded(masses.isEmpty());
    }
}

void MassModel::loadData()
{
    m_liturgyRepository->loadMasses(LiturgyIdentifierKeyFactory::getPair(m_date, m_zone));
}