/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef READING_H
#define READING_H

#include <QObject>
#include <QString>

class Reading : public QObject {
    Q_OBJECT

  public:
    enum ReadingType {
        Unknown = 0,
        Lecture1,
        Lecture2,
        Lecture3,
        Lecture4,
        Lecture5,
        Lecture6,
        Lecture7,
        Lecture8,
        Lecture9,
        Lecture10,
        Psaume,
        Cantique,
        Evangile,
        EvangileLong,
        EvangileCourt,
        Sequence,
        EntreeMessianique,
        Introduction,
        PsaumeInvitatoire,
        Hymne,
        VersetPsaume,
        Psalm,
        Canticle,
        CantiqueMariale,
        Pericope,
        Lecture,
        TextePatristique,
        Intercession,
        NotrePere,
        Oraison,
        TeDeum,
        Messes
    };
    Q_ENUM(ReadingType)

    explicit Reading(QObject* parent = nullptr);
    explicit Reading(ReadingType readingType, const QString& refrainPsalm, const QString& title,
                     const QString& editor, const QString& author, const QString& content,
                     const QString& reference, const QString& introRead, const QString& gospelVerse,
                     const QString& refrainReference, QObject* parent = nullptr);

    Q_PROPERTY(ReadingType readingType READ readingType CONSTANT)
    Q_PROPERTY(QString refrainPsalm READ refrainPsalm CONSTANT)
    Q_PROPERTY(QString author READ author CONSTANT)
    Q_PROPERTY(QString editor READ editor CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString content READ content CONSTANT)
    Q_PROPERTY(QString reference READ reference CONSTANT)
    Q_PROPERTY(QString introRead READ introRead CONSTANT)
    Q_PROPERTY(QString gospelVerse READ gospelVerse CONSTANT)
    Q_PROPERTY(QString refrainReference READ refrainReference CONSTANT)

    ReadingType readingType() const;
    QString refrainPsalm() const;
    QString author() const;
    QString editor() const;
    QString title() const;
    QString content() const;
    QString reference() const;
    QString introRead() const;
    QString gospelVerse() const;
    QString refrainReference() const;

  private:
    ReadingType m_readingType;
    QString m_refrainPsalm;
    QString m_title;
    QString m_content;
    QString m_reference;
    QString m_introRead;
    QString m_gospelVerse;
    QString m_refrainReference;
    QString m_editor;
    QString m_author;
};

#endif // READING_H
