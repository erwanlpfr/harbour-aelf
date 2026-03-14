/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef READINGTABMODEL_H
#define READINGTABMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QList>
#include <QObject>

class QQmlEngine;
class QQmlComponent;
class Reading;

class ReadingTabModel : public QAbstractListModel {
    Q_OBJECT

  public:
    enum Roles { TitleRole = Qt::UserRole + 1, SourceRole, ReadingRole };

    static void setEngine(QQmlEngine* engine);
    static QQmlEngine* engine();

    explicit ReadingTabModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setReadings(QList<Reading*> readings);
    QList<Reading*> readings() const;

    static QString getTitleForReading(Reading* reading);

  private:
    static QQmlEngine* s_engine;

    QHash<int, QByteArray> m_roles;
    QList<Reading*> m_readings;
};

#endif // READINGTABMODEL_H
