/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef HOURLITURGY_H
#define HOURLITURGY_H

#include <QObject>
#include <QList>
#include <QString>

class Reading;
class ReadingTabModel;

class HourLiturgy : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString type READ type CONSTANT)
    Q_PROPERTY(ReadingTabModel* readingsModel READ readingsModel CONSTANT)

public:
    enum HourType {
        Compline,
        Lauds,
        Lectures,
        None,
        Sext,
        Terce,
        Vespers
    };
    Q_ENUMS(HourType)

    explicit HourLiturgy(QObject* parent = nullptr);
    explicit HourLiturgy(HourType type, QList<Reading*> readings, QObject* parent = nullptr);

    QString type() const;
    ReadingTabModel* readingsModel() const;
    static QString typeToString(HourType type);
    HourType hourType() const;

private:
    HourType m_type;
    ReadingTabModel* m_readingsModel;
};

#endif // HOURLITURGY_H
