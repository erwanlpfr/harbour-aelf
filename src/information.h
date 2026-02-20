/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INFORMATION_H
#define INFORMATION_H

#include <QColor>
#include <QObject>
#include <QString>

class Information : public QObject {
    Q_OBJECT

public:
    explicit Information(QObject* parent = nullptr);
    explicit Information(const QJsonObject& informationObject, QObject* parent = nullptr);
    explicit Information(
        const QString& date,
        const QString& liturgicalZone,
        const QString& color,
        int year,
        const QString& liturgicalTime,
        int week,
        int day,
        const QString& liturgicalDayName,
        const QString& holiday,
        const QString& degree,
        const QString& line1,
        const QString& line2,
        const QString& line3,
        const QString& color2,
        const QString& color3,
        QObject* parent = nullptr);

    Q_PROPERTY(QString date READ date CONSTANT)
    Q_PROPERTY(QString liturgicalZone READ location CONSTANT)
    Q_PROPERTY(QColor color READ color CONSTANT)
    Q_PROPERTY(int year READ year CONSTANT)
    Q_PROPERTY(QString liturgicalTime READ liturgicalTime CONSTANT)
    Q_PROPERTY(int week READ week CONSTANT)
    Q_PROPERTY(int day READ day CONSTANT)
    Q_PROPERTY(QString liturgicalDayName READ liturgicalDayName CONSTANT)
    Q_PROPERTY(QString holiday READ holiday CONSTANT)
    Q_PROPERTY(QString degree READ degree CONSTANT)
    Q_PROPERTY(QString line1 READ line1 CONSTANT)
    Q_PROPERTY(QString line2 READ line2 CONSTANT)
    Q_PROPERTY(QString line3 READ line3 CONSTANT)
    Q_PROPERTY(QColor color2 READ color2 CONSTANT)
    Q_PROPERTY(QColor color3 READ color3 CONSTANT)

    QString date() const;
    QString location() const;
    QColor color() const;
    int year() const;
    QString liturgicalTime() const;
    int week() const;
    int day() const;
    QString liturgicalDayName() const;
    QString holiday() const;
    QString degree() const;
    QString line1() const;
    QString line2() const;
    QString line3() const;
    QColor color2() const;
    QColor color3() const;

private:
    QString m_date;
    QString m_liturgicalZone;
    QColor m_color;
    int m_year;
    QString m_liturgicalTime;
    int m_week;
    int m_day;
    QString m_liturgicalDayName;
    QString m_holiday;
    QString m_degree;
    QString m_line1;
    QString m_line2;
    QString m_line3;
    QColor m_color2;
    QColor m_color3;
};

#endif // INFORMATION_H
