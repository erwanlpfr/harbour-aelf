/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INFORMATIONMODEL_H
#define INFORMATIONMODEL_H

#include "information.h"
#include "liturgybasemodel.h"
#include "liturgyidentifierkey.h"
#include <QObject>

class InformationModel : public LiturgyBaseModel {
    Q_OBJECT

    Q_PROPERTY(Information* information READ information NOTIFY informationChanged)

  public:
    explicit InformationModel(QObject* parent = nullptr);

    Information* information() const;

  signals:
    void informationChanged();

  private slots:
    void onInformationChanged(const LiturgyIdentifierKey& key, Information* information);

  protected:
    void loadData() override;

  private:
    Information* m_information;
};

#endif // INFORMATIONMODEL_H
