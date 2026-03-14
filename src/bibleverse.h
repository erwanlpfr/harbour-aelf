/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BIBLEVERSE_H
#define BIBLEVERSE_H

#include <QObject>
#include <QString>

class BibleVerse : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString bookCode READ bookCode CONSTANT)
    Q_PROPERTY(int chapter READ chapter CONSTANT)
    Q_PROPERTY(int verseNumber READ verseNumber CONSTANT)
    Q_PROPERTY(QString text READ text CONSTANT)

  public:
    explicit BibleVerse(const QString& bookCode, int chapter, int verseNumber, const QString& text,
                        QObject* parent = nullptr);

    QString bookCode() const {
        return m_bookCode;
    }
    int chapter() const {
        return m_chapter;
    }
    int verseNumber() const {
        return m_verseNumber;
    }
    QString text() const {
        return m_text;
    }

  private:
    QString m_bookCode;
    int m_chapter;
    int m_verseNumber;
    QString m_text;
};

#endif // BIBLEVERSE_H
