/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "mass.h"
#include "reading.h"
#include "readingtabmodel.h"
#include <QMetaType>

Mass::Mass(QObject* parent)
    : QObject(parent)
    , m_name()
    , m_readingsModel(new ReadingTabModel(this))
{
}

Mass::Mass(const QString& name, QList<Reading*> readings, QObject* parent)
    : QObject(parent)
    , m_name(name)
    , m_readingsModel(new ReadingTabModel(this))
{
    m_readingsModel->setReadings(readings);
}

QString Mass::name() const
{
    return m_name;
}

ReadingTabModel* Mass::readingsModel() const
{
    return m_readingsModel;
}
