/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef ZONE_H
#define ZONE_H

#include <QObject>
#include <QString>

class Zone : public QObject {
    Q_OBJECT
    Q_ENUMS(LiturgicalZone)

  public:
    enum LiturgicalZone { Afrique, Belgique, Canada, France, Luxembourg, Romain, Suisse };

    static QString toString(LiturgicalZone zone);
    static LiturgicalZone fromString(const QString& zoneStr);
    static QStringList getAllZones();
};

#endif // ZONE_H
