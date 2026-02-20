/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "readingtabmodel.h"
#include "reading.h"
#include "sailfishapp.h"
#include <QDebug>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlEngine>
#include <QCoreApplication>
#include <QMap>

QQmlEngine* ReadingTabModel::s_engine = nullptr;

void ReadingTabModel::setEngine(QQmlEngine* engine) {
  s_engine = engine;
}

QQmlEngine* ReadingTabModel::engine() {
  return s_engine;
}

QString ReadingTabModel::getTitleForReading(Reading* reading)
{
    if (!reading) return QString();
    
    Reading::ReadingType type = reading->readingType();
    
    if (type == Reading::Psalm) {
        QString reference = reading->reference();
        if (reference.startsWith("Ps ")) {
            reference = reference.mid(3);
        }
        return QCoreApplication::translate("Reading", "Psaume") + " " + reference;
    }
    
    if (type == Reading::Canticle) {
        QString title = reading->title();
        return title.isEmpty() ? QCoreApplication::translate("Reading", "Cantique") : title;
    }
    
    if (type == Reading::CantiqueMariale) {
        QString title = reading->title();
        return title.isEmpty() ? QCoreApplication::translate("Reading", "Cantique de Marie") : title;
    }
    
    static const QMap<Reading::ReadingType, const char*> typeNames = {
        {Reading::Unknown, QT_TRANSLATE_NOOP("Reading", "Inconnu")},
        {Reading::Lecture1, QT_TRANSLATE_NOOP("Reading", "Première Lecture")},
        {Reading::Lecture2, QT_TRANSLATE_NOOP("Reading", "Deuxième Lecture")},
        {Reading::Lecture3, QT_TRANSLATE_NOOP("Reading", "Troisième Lecture")},
        {Reading::Lecture4, QT_TRANSLATE_NOOP("Reading", "Quatrième Lecture")},
        {Reading::Lecture5, QT_TRANSLATE_NOOP("Reading", "Cinquième Lecture")},
        {Reading::Lecture6, QT_TRANSLATE_NOOP("Reading", "Sixième Lecture")},
        {Reading::Lecture7, QT_TRANSLATE_NOOP("Reading", "Septième Lecture")},
        {Reading::Lecture8, QT_TRANSLATE_NOOP("Reading", "Huitième Lecture")},
        {Reading::Lecture9, QT_TRANSLATE_NOOP("Reading", "Neuvième Lecture")},
        {Reading::Lecture10, QT_TRANSLATE_NOOP("Reading", "Dixième Lecture")},
        {Reading::Psaume, QT_TRANSLATE_NOOP("Reading", "Psaume")},
        {Reading::Cantique, QT_TRANSLATE_NOOP("Reading", "Cantique")},
        {Reading::Evangile, QT_TRANSLATE_NOOP("Reading", "Évangile")},
        {Reading::EvangileLong, QT_TRANSLATE_NOOP("Reading", "Évangile (lecture longue)")},
        {Reading::EvangileCourt, QT_TRANSLATE_NOOP("Reading", "Évangile (lecture brève)")},
        {Reading::Sequence, QT_TRANSLATE_NOOP("Reading", "Séquence")},
        {Reading::EntreeMessianique, QT_TRANSLATE_NOOP("Reading", "Entrée messianique")},
        {Reading::Introduction, QT_TRANSLATE_NOOP("Reading", "Introduction")},
        {Reading::PsaumeInvitatoire, QT_TRANSLATE_NOOP("Reading", "Antienne invitatoire")},
        {Reading::Hymne, QT_TRANSLATE_NOOP("Reading", "Hymne")},
        {Reading::VersetPsaume, QT_TRANSLATE_NOOP("Reading", "Verset")},
        {Reading::Psalm, QT_TRANSLATE_NOOP("Reading", "Psaume")},
        {Reading::Canticle, QT_TRANSLATE_NOOP("Reading", "Canticle")},
        {Reading::Pericope, QT_TRANSLATE_NOOP("Reading", "Parole de Dieu")},
        {Reading::Lecture, QT_TRANSLATE_NOOP("Reading", "Lecture")},
        {Reading::TextePatristique, QT_TRANSLATE_NOOP("Reading", "Lecture patristique")},
        {Reading::Intercession, QT_TRANSLATE_NOOP("Reading", "Intercession")},
        {Reading::NotrePere, QT_TRANSLATE_NOOP("Reading", "Notre Père")},
        {Reading::Oraison, QT_TRANSLATE_NOOP("Reading", "Oraison et bénédiction")},
        {Reading::TeDeum, QT_TRANSLATE_NOOP("Reading", "Te Deum")},
        {Reading::Messes, QT_TRANSLATE_NOOP("Reading", "Messes")}
    };
    
    auto it = typeNames.find(type);
    return it != typeNames.end() 
        ? QCoreApplication::translate("Reading", it.value())
        : QString();
}

ReadingTabModel::ReadingTabModel(QObject *parent)
    : QAbstractListModel(parent) {
  m_roles[TitleRole] = "title";
  m_roles[SourceRole] = "source";
  m_roles[ReadingRole] = "reading";
}

int ReadingTabModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return m_readings.count();
}

QVariant ReadingTabModel::data(const QModelIndex &index, int role) const {
  QVariant result = QVariant();

  if (!index.isValid() || index.row() >= m_readings.count()) {
    return result;
  }

  Reading *reading = m_readings[index.row()];

  switch (role) {
  case TitleRole:
    result = getTitleForReading(reading);
    break;
  case SourceRole:
    result = QUrl(SailfishApp::pathTo("qml/components/layout/Reading.qml"));
    break;
  case ReadingRole:
    result = QVariant::fromValue(reading);
    break;
  }

  return result;
}

QHash<int, QByteArray> ReadingTabModel::roleNames() const { 
  return m_roles; 
}

void ReadingTabModel::setReadings(QList<Reading *> readings) {
  beginResetModel();
  m_readings = readings;
  endResetModel();
}

QList<Reading *> ReadingTabModel::readings() const { 
  return m_readings; 
}
