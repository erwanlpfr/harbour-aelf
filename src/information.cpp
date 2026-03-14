/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "information.h"
#include "liturgicalcolorhelper.h"
#include <QJsonObject>
#include <QString>

Information::Information(QObject* parent) : QObject(parent) {
}

Information::Information(const QJsonObject& json, QObject* parent)
    : Information(json.value("date").toString(), json.value("zone").toString(),
                  json.value("couleur").toString(), json.value("annee").toInt(),
                  json.value("temps_liturgique").toString(), json.value("semaine").toInt(),
                  json.value("jour").toInt(), json.value("jour_liturgique_nom").toString(),
                  json.value("fete").toString(), json.value("degre").toString(),
                  json.value("ligne1").toString(), json.value("ligne2").toString(),
                  json.value("ligne3").toString(), json.value("couleur2").toString(),
                  json.value("couleur3").toString(), parent) {
}

Information::Information(const QString& date, const QString& liturgicalZone, const QString& color,
                         int year, const QString& liturgicalTime, int week, int day,
                         const QString& liturgicalDayName, const QString& holiday,
                         const QString& degree, const QString& line1, const QString& line2,
                         const QString& line3, const QString& color2, const QString& color3,
                         QObject* parent)
    : QObject(parent), m_date(date), m_liturgicalZone(liturgicalZone),
      m_color(LiturgicalColorHelper::getColorFromString(color)), m_year(year),
      m_liturgicalTime(liturgicalTime), m_week(week), m_day(day),
      m_liturgicalDayName(liturgicalDayName), m_holiday(holiday), m_degree(degree), m_line1(line1),
      m_line2(line2), m_line3(line3), m_color2(LiturgicalColorHelper::getColorFromString(color2)),
      m_color3(LiturgicalColorHelper::getColorFromString(color3)) {
}

QString Information::date() const {
    return m_date;
}
QString Information::location() const {
    return m_liturgicalZone;
}
QColor Information::color() const {
    return m_color;
}
int Information::year() const {
    return m_year;
}
QString Information::liturgicalTime() const {
    return m_liturgicalTime;
}
int Information::week() const {
    return m_week;
}
int Information::day() const {
    return m_day;
}
QString Information::liturgicalDayName() const {
    return m_liturgicalDayName;
}
QString Information::holiday() const {
    return m_holiday;
}
QString Information::degree() const {
    return m_degree;
}
QString Information::line1() const {
    return m_line1;
}
QString Information::line2() const {
    return m_line2;
}
QString Information::line3() const {
    return m_line3;
}
QColor Information::color2() const {
    return m_color2;
}
QColor Information::color3() const {
    return m_color3;
}
