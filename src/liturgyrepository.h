/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef LITURGYREPOSITORY_H
#define LITURGYREPOSITORY_H

#include "hourliturgy.h"
#include "liturgyidentifierkey.h"
#include <QDate>
#include <QList>
#include <QMap>
#include <QObject>
#include <QString>

class LiturgyService;
class Information;
class Mass;

class LiturgyRepository : public QObject {
    Q_OBJECT

  public:
    static LiturgyRepository* instance(QObject* parent = nullptr);
    ~LiturgyRepository();

    void loadInformation(const LiturgyIdentifierKey& key);
    void loadMasses(const LiturgyIdentifierKey& key);
    void loadHourLiturgy(const LiturgyIdentifierKey& key, HourLiturgy::HourType type);

  signals:
    void informationChanged(const LiturgyIdentifierKey& key, Information* information);
    void massesChanged(const LiturgyIdentifierKey& key, QList<Mass*> masses);
    void hourLiturgyChanged(const LiturgyIdentifierKey& key, HourLiturgy::HourType type,
                            HourLiturgy* hourLiturgy);
    void errorOccurred(const LiturgyIdentifierKey& key, const QString& error);

  public slots:
    void onInformationFetched(const LiturgyIdentifierKey& key, Information* information);
    void onMassesFetched(const LiturgyIdentifierKey& key, QList<Mass*> masses);
    void onHourLiturgyFetched(const LiturgyIdentifierKey& key, HourLiturgy::HourType type,
                              HourLiturgy* hourLiturgy);
    void onErrorOccurred(const LiturgyIdentifierKey& key, const QString& error);

  private slots:
    void onServiceInformationFetched(const QDate& date, const QString& zone,
                                     Information* information);
    void onServiceMassesFetched(const QDate& date, const QString& zone, QList<Mass*> masses);
    void onServiceHourLiturgyFetched(const QDate& date, const QString& zone,
                                     HourLiturgy::HourType type, HourLiturgy* hourLiturgy);
    void onServiceErrorOccurred(const QDate& date, const QString& zone, const QString& error);

  private:
    explicit LiturgyRepository(QObject* parent = nullptr);
    static LiturgyRepository* s_instance;

    LiturgyIdentifierKey createKey(const QDate& date, const QString& zone) const;

    LiturgyService* m_service;
    QMap<LiturgyIdentifierKey, Information*> m_informationMap;
    QMap<LiturgyIdentifierKey, QList<Mass*>> m_massesMap;
    QMap<HourLiturgyKey, HourLiturgy*> m_hourLiturgyMap;
};

#endif // LITURGYREPOSITORY_H
