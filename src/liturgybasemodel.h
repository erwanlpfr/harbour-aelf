/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef LITURGYBASEMODEL_H
#define LITURGYBASEMODEL_H

#include <QDate>
#include <QObject>
#include <QString>

class LiturgyRepository;

class LiturgyBaseModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(QString zone READ zone WRITE setZone NOTIFY zoneChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
    Q_PROPERTY(bool empty READ empty NOTIFY emptyChanged)

  public:
    explicit LiturgyBaseModel(QObject* parent = nullptr);

    QDate date() const;
    void setDate(const QDate& date);

    QString zone() const;
    void setZone(const QString& zone);

    bool loading() const;
    void setLoading(bool loading);

    QString error() const;
    void setError(const QString& error);

    bool empty() const;
    void setEmpty(bool empty);

  signals:
    void dateChanged();
    void zoneChanged();
    void loadingChanged();
    void errorChanged();
    void emptyChanged();

  protected:
    LiturgyRepository* m_liturgyRepository;
    QDate m_date;
    QString m_zone;
    bool m_loading;
    QString m_error;
    bool m_empty;

    virtual void loadData() = 0;
    void setDataLoaded(bool empty);
};

#endif // LITURGYBASEMODEL_H
