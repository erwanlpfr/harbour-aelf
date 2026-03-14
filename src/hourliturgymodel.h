/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef HOURLITURGYMODEL_H
#define HOURLITURGYMODEL_H

#include "hourliturgy.h"
#include "informationmodel.h"
#include "liturgyidentifierkey.h"
#include <QObject>

class HourLiturgyModel : public InformationModel {
    Q_OBJECT

    Q_PROPERTY(HourLiturgy::HourType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(HourLiturgy* hourLiturgy READ hourLiturgy NOTIFY hourLiturgyChanged)

  public:
    explicit HourLiturgyModel(QObject* parent = nullptr);

    HourLiturgy::HourType type() const;
    void setType(HourLiturgy::HourType type);

    HourLiturgy* hourLiturgy() const;

  signals:
    void typeChanged();
    void hourLiturgyChanged();

  private slots:
    void onHourLiturgyChanged(const LiturgyIdentifierKey& key, HourLiturgy::HourType type,
                              HourLiturgy* hourLiturgy);

  protected:
    void loadData() override;

  private:
    HourLiturgy::HourType m_type;
    HourLiturgy* m_hourLiturgy;
};

#endif // HOURLITURGYMODEL_H
