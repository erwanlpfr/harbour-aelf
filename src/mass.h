/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef MASS_H
#define MASS_H

#include <QObject>
#include <QString>

class Reading;
class ReadingTabModel;

class Mass : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(ReadingTabModel* readingsModel READ readingsModel CONSTANT)

  public:
    explicit Mass(QObject* parent = nullptr);
    explicit Mass(const QString& name, QList<Reading*> readings, QObject* parent = nullptr);

    QString name() const;
    ReadingTabModel* readingsModel() const;

  private:
    QString m_name;
    ReadingTabModel* m_readingsModel;
};

#endif // MASS_H
