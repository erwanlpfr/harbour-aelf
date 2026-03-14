/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "hourliturgy.h"
#include "reading.h"
#include "readingtabmodel.h"
#include <QMetaType>

HourLiturgy::HourLiturgy(QObject* parent)
    : QObject(parent), m_type(Vespers), m_readingsModel(new ReadingTabModel(this)) {
}

HourLiturgy::HourLiturgy(HourType type, QList<Reading*> readings, QObject* parent)
    : QObject(parent), m_type(type), m_readingsModel(new ReadingTabModel(this)) {
    m_readingsModel->setReadings(readings);
}

QString HourLiturgy::type() const {
    return typeToString(m_type);
}

HourLiturgy::HourType HourLiturgy::hourType() const {
    return m_type;
}

ReadingTabModel* HourLiturgy::readingsModel() const {
    return m_readingsModel;
}

QString HourLiturgy::typeToString(HourType type) {
    switch (type) {
    case Compline:
        return "complies";
    case Lauds:
        return "laudes";
    case Lectures:
        return "lectures";
    case None:
        return "none";
    case Sext:
        return "sexte";
    case Terce:
        return "tierce";
    case Vespers:
        return "vepres";
    default:
        return "vepres";
    }
}
