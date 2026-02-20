/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INFORMATIONMODEL_H
#define INFORMATIONMODEL_H

#include "liturgybasemodel.h"
#include "information.h"
#include <QObject>
#include "liturgyidentifierkey.h"

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
