/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "zone.h"

QString Zone::toString(LiturgicalZone zone) {
    switch (zone) {
    case Afrique:
        return "afrique";
    case Belgique:
        return "belgique";
    case Canada:
        return "canada";
    case France:
        return "france";
    case Luxembourg:
        return "luxembourg";
    case Romain:
        return "romain";
    case Suisse:
        return "suisse";
    default:
        return "france";
    }
}

Zone::LiturgicalZone Zone::fromString(const QString& zoneStr) {
    if (zoneStr == "afrique")
        return Afrique;
    if (zoneStr == "belgique")
        return Belgique;
    if (zoneStr == "canada")
        return Canada;
    if (zoneStr == "france")
        return France;
    if (zoneStr == "luxembourg")
        return Luxembourg;
    if (zoneStr == "romain")
        return Romain;
    if (zoneStr == "suisse")
        return Suisse;
    return France;
}

QStringList Zone::getAllZones() {
    return {"afrique", "belgique", "canada", "france", "luxembourg", "romain", "suisse"};
}
