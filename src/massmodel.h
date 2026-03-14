/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef MASSMODEL_H
#define MASSMODEL_H

#include "informationmodel.h"
#include "liturgyidentifierkey.h"
#include "mass.h"
#include <QObject>
#include <QStringList>

class MassModel : public InformationModel {
    Q_OBJECT

    Q_PROPERTY(QStringList massNames READ massNames NOTIFY massNamesChanged)
    Q_PROPERTY(Mass* currentMass READ currentMass NOTIFY currentMassChanged)
    Q_PROPERTY(int currentMassIndex READ currentMassIndex WRITE setCurrentMassIndex NOTIFY
                   currentMassIndexChanged)

  public:
    explicit MassModel(QObject* parent = nullptr);

    QStringList massNames() const;
    Mass* currentMass() const;
    int currentMassIndex() const;
    void setCurrentMassIndex(int index);

  signals:
    void massNamesChanged();
    void currentMassChanged();
    void currentMassIndexChanged();

  private slots:
    void onMassesChanged(const LiturgyIdentifierKey& key, QList<Mass*> masses);

  protected:
    void loadData() override;

  private:
    QList<Mass*> m_masses;
    int m_currentMassIndex;
};

#endif // MASSMODEL_H
