/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BIBLEBOOK_H
#define BIBLEBOOK_H

#include <QObject>
#include <QString>

class BibleBook : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString code READ code CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString abbreviation READ abbreviation CONSTANT)
    Q_PROPERTY(int chapterCount READ chapterCount CONSTANT)
    Q_PROPERTY(QString section READ section CONSTANT)

public:
    explicit BibleBook(const QString& code, const QString& name, 
                      const QString& abbreviation, int chapterCount,
                      const QString& section, QObject* parent = nullptr);

    QString code() const { return m_code; }
    QString name() const { return m_name; }
    QString abbreviation() const { return m_abbreviation; }
    int chapterCount() const { return m_chapterCount; }
    QString section() const { return m_section; }

private:
    QString m_code;
    QString m_name;
    QString m_abbreviation;
    int m_chapterCount;
    QString m_section;
};

#endif // BIBLEBOOK_H
