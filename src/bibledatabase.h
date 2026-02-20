/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BIBLEDATABASE_H
#define BIBLEDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>
#include <QList>
#include <QMap>
#include <QPair>

class BibleBook;
class BibleVerse;

class BibleDatabase : public QObject {
    Q_OBJECT

public:
    static BibleDatabase* instance();
    
    bool initialize();
    bool isInitialized() const { return m_initialized; }
    Q_INVOKABLE void ensureInitialized();
    
    QList<BibleBook*> getBooks();
    QList<BibleVerse*> getVerses(const QString& bookCode, int chapter);
    
    Q_INVOKABLE QString getBookCodeFromAbbreviation(const QString& abbreviation) const;

signals:
    void initializationStarted();
    void initializationCompleted(bool success);
    void initializationFailed(const QString& error);

private:
    explicit BibleDatabase(QObject* parent = nullptr);
    ~BibleDatabase();
    
    QString getDatabasePath() const;
    void loadBookMetadata();
    bool validateDatabaseStructure();
    
    static BibleDatabase* s_instance;
    
    QSqlDatabase m_database;
    bool m_initialized;
    bool m_initializing;
    QMap<QString, QPair<QString, int>> m_bookMetadata;
};

#endif // BIBLEDATABASE_H
