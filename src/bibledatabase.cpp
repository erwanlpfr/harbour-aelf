/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "bibledatabase.h"
#include "biblebook.h"
#include "bibleverse.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QFileInfo>
#include <QtConcurrent>

BibleDatabase* BibleDatabase::s_instance = nullptr;

BibleDatabase::BibleDatabase(QObject* parent)
    : QObject(parent)
    , m_initialized(false)
{
}

BibleDatabase::~BibleDatabase()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
}

BibleDatabase* BibleDatabase::instance()
{
    if (!s_instance) {
        s_instance = new BibleDatabase();
    }
    return s_instance;
}

QString BibleDatabase::getDatabasePath() const
{
    return "/usr/share/harbour-aelf/bible.db";
}

struct BookMetadata {
    QString code;
    QString name;
    QString abbreviation;
    int chapters;
};

QList<BookMetadata> getUnifiedBookMetadata()
{
    static QList<BookMetadata> books;
    if (books.isEmpty()) {
        books = {
            {"Gn", QCoreApplication::translate("BibleDatabase", "Genèse"), QCoreApplication::translate("BibleDatabase", "Gen"), 50},
            {"Ex", QCoreApplication::translate("BibleDatabase", "Exode"), QCoreApplication::translate("BibleDatabase", "Exo"), 40},
            {"Lv", QCoreApplication::translate("BibleDatabase", "Lévitique"), QCoreApplication::translate("BibleDatabase", "Lév"), 27},
            {"Nb", QCoreApplication::translate("BibleDatabase", "Nombres"), QCoreApplication::translate("BibleDatabase", "Nom"), 36},
            {"Dt", QCoreApplication::translate("BibleDatabase", "Deutéronome"), QCoreApplication::translate("BibleDatabase", "Deu"), 34},
            {"Jos", QCoreApplication::translate("BibleDatabase", "Josué"), QCoreApplication::translate("BibleDatabase", "Jos"), 24},
            {"Jg", QCoreApplication::translate("BibleDatabase", "Juges"), QCoreApplication::translate("BibleDatabase", "Jug"), 21},
            {"Rt", QCoreApplication::translate("BibleDatabase", "Ruth"), QCoreApplication::translate("BibleDatabase", "Rut"), 4},
            {"1S", QCoreApplication::translate("BibleDatabase", "1 Samuel"), QCoreApplication::translate("BibleDatabase", "1Sa"), 31},
            {"2S", QCoreApplication::translate("BibleDatabase", "2 Samuel"), QCoreApplication::translate("BibleDatabase", "2Sa"), 24},
            {"1R", QCoreApplication::translate("BibleDatabase", "1 Rois"), QCoreApplication::translate("BibleDatabase", "1Ro"), 22},
            {"2R", QCoreApplication::translate("BibleDatabase", "2 Rois"), QCoreApplication::translate("BibleDatabase", "2Ro"), 25},
            {"1Ch", QCoreApplication::translate("BibleDatabase", "1 Chroniques"), QCoreApplication::translate("BibleDatabase", "1Ch"), 29},
            {"2Ch", QCoreApplication::translate("BibleDatabase", "2 Chroniques"), QCoreApplication::translate("BibleDatabase", "2Ch"), 36},
            {"Esd", QCoreApplication::translate("BibleDatabase", "Esdras"), QCoreApplication::translate("BibleDatabase", "Esd"), 10},
            {"Ne", QCoreApplication::translate("BibleDatabase", "Néhémie"), QCoreApplication::translate("BibleDatabase", "Néh"), 13},
            {"Est", QCoreApplication::translate("BibleDatabase", "Esther"), QCoreApplication::translate("BibleDatabase", "Est"), 10},
            {"Jb", QCoreApplication::translate("BibleDatabase", "Job"), QCoreApplication::translate("BibleDatabase", "Job"), 42},
            {"Ps", QCoreApplication::translate("BibleDatabase", "Psaumes"), QCoreApplication::translate("BibleDatabase", "Psa"), 150},
            {"Pr", QCoreApplication::translate("BibleDatabase", "Proverbes"), QCoreApplication::translate("BibleDatabase", "Pro"), 31},
            {"Qo", QCoreApplication::translate("BibleDatabase", "Ecclésiaste"), QCoreApplication::translate("BibleDatabase", "Ecc"), 12},
            {"Ct", QCoreApplication::translate("BibleDatabase", "Cantique"), QCoreApplication::translate("BibleDatabase", "Can"), 8},
            {"Is", QCoreApplication::translate("BibleDatabase", "Esaïe"), QCoreApplication::translate("BibleDatabase", "Esa"), 66},
            {"Jr", QCoreApplication::translate("BibleDatabase", "Jérémie"), QCoreApplication::translate("BibleDatabase", "Jér"), 52},
            {"Lm", QCoreApplication::translate("BibleDatabase", "Lamentations"), QCoreApplication::translate("BibleDatabase", "Lam"), 5},
            {"Ez", QCoreApplication::translate("BibleDatabase", "Ezéchiel"), QCoreApplication::translate("BibleDatabase", "Eze"), 48},
            {"Dn", QCoreApplication::translate("BibleDatabase", "Daniel"), QCoreApplication::translate("BibleDatabase", "Dan"), 12},
            {"Os", QCoreApplication::translate("BibleDatabase", "Osée"), QCoreApplication::translate("BibleDatabase", "Osé"), 14},
            {"Jl", QCoreApplication::translate("BibleDatabase", "Joël"), QCoreApplication::translate("BibleDatabase", "Joë"), 3},
            {"Am", QCoreApplication::translate("BibleDatabase", "Amos"), QCoreApplication::translate("BibleDatabase", "Amo"), 9},
            {"Ab", QCoreApplication::translate("BibleDatabase", "Abdias"), QCoreApplication::translate("BibleDatabase", "Abd"), 1},
            {"Jon", QCoreApplication::translate("BibleDatabase", "Jonas"), QCoreApplication::translate("BibleDatabase", "Jon"), 4},
            {"Mi", QCoreApplication::translate("BibleDatabase", "Michée"), QCoreApplication::translate("BibleDatabase", "Mic"), 7},
            {"Na", QCoreApplication::translate("BibleDatabase", "Nahum"), QCoreApplication::translate("BibleDatabase", "Nah"), 3},
            {"Ha", QCoreApplication::translate("BibleDatabase", "Habacuc"), QCoreApplication::translate("BibleDatabase", "Hab"), 3},
            {"So", QCoreApplication::translate("BibleDatabase", "Sophonie"), QCoreApplication::translate("BibleDatabase", "Soph"), 3},
            {"Ag", QCoreApplication::translate("BibleDatabase", "Aggée"), QCoreApplication::translate("BibleDatabase", "Agg"), 2},
            {"Za", QCoreApplication::translate("BibleDatabase", "Zacharie"), QCoreApplication::translate("BibleDatabase", "Zac"), 14},
            {"Ml", QCoreApplication::translate("BibleDatabase", "Malachie"), QCoreApplication::translate("BibleDatabase", "Mal"), 4},
            {"Mt", QCoreApplication::translate("BibleDatabase", "Matthieu"), QCoreApplication::translate("BibleDatabase", "Mat"), 28},
            {"Mc", QCoreApplication::translate("BibleDatabase", "Marc"), QCoreApplication::translate("BibleDatabase", "Mar"), 16},
            {"Lc", QCoreApplication::translate("BibleDatabase", "Luc"), QCoreApplication::translate("BibleDatabase", "Luc"), 24},
            {"Jn", QCoreApplication::translate("BibleDatabase", "Jean"), QCoreApplication::translate("BibleDatabase", "Jea"), 21},
            {"Ac", QCoreApplication::translate("BibleDatabase", "Actes"), QCoreApplication::translate("BibleDatabase", "Act"), 28},
            {"Rm", QCoreApplication::translate("BibleDatabase", "Romains"), QCoreApplication::translate("BibleDatabase", "Rom"), 16},
            {"1Co", QCoreApplication::translate("BibleDatabase", "1 Corinthiens"), QCoreApplication::translate("BibleDatabase", "1Co"), 16},
            {"2Co", QCoreApplication::translate("BibleDatabase", "2 Corinthiens"), QCoreApplication::translate("BibleDatabase", "2Co"), 13},
            {"Ga", QCoreApplication::translate("BibleDatabase", "Galates"), QCoreApplication::translate("BibleDatabase", "Gal"), 6},
            {"Ep", QCoreApplication::translate("BibleDatabase", "Ephésiens"), QCoreApplication::translate("BibleDatabase", "Eph"), 6},
            {"Ph", QCoreApplication::translate("BibleDatabase", "Philippiens"), QCoreApplication::translate("BibleDatabase", "Phi"), 4},
            {"Col", QCoreApplication::translate("BibleDatabase", "Colossiens"), QCoreApplication::translate("BibleDatabase", "Col"), 4},
            {"1Th", QCoreApplication::translate("BibleDatabase", "1 Thessaloniciens"), QCoreApplication::translate("BibleDatabase", "1Th"), 5},
            {"2Th", QCoreApplication::translate("BibleDatabase", "2 Thessaloniciens"), QCoreApplication::translate("BibleDatabase", "2Th"), 3},
            {"1Tm", QCoreApplication::translate("BibleDatabase", "1 Timothée"), QCoreApplication::translate("BibleDatabase", "1Ti"), 6},
            {"2Tm", QCoreApplication::translate("BibleDatabase", "2 Timothée"), QCoreApplication::translate("BibleDatabase", "2Ti"), 4},
            {"Tt", QCoreApplication::translate("BibleDatabase", "Tite"), QCoreApplication::translate("BibleDatabase", "Tit"), 3},
            {"Phm", QCoreApplication::translate("BibleDatabase", "Philémon"), QCoreApplication::translate("BibleDatabase", "Phm"), 1},
            {"He", QCoreApplication::translate("BibleDatabase", "Hébreux"), QCoreApplication::translate("BibleDatabase", "Héb"), 13},
            {"Jc", QCoreApplication::translate("BibleDatabase", "Jacques"), QCoreApplication::translate("BibleDatabase", "Jac"), 5},
            {"1P", QCoreApplication::translate("BibleDatabase", "1 Pierre"), QCoreApplication::translate("BibleDatabase", "1Pi"), 5},
            {"2P", QCoreApplication::translate("BibleDatabase", "2 Pierre"), QCoreApplication::translate("BibleDatabase", "2Pi"), 3},
            {"1Jn", QCoreApplication::translate("BibleDatabase", "1 Jean"), QCoreApplication::translate("BibleDatabase", "1Je"), 5},
            {"2Jn", QCoreApplication::translate("BibleDatabase", "2 Jean"), QCoreApplication::translate("BibleDatabase", "2Je"), 1},
            {"3Jn", QCoreApplication::translate("BibleDatabase", "3 Jean"), QCoreApplication::translate("BibleDatabase", "3Je"), 1},
            {"Jude", QCoreApplication::translate("BibleDatabase", "Jude"), QCoreApplication::translate("BibleDatabase", "Jud"), 1},
            {"Ap", QCoreApplication::translate("BibleDatabase", "Apocalypse"), QCoreApplication::translate("BibleDatabase", "Apo"), 22}
        };
    }
    return books;
}

void BibleDatabase::loadBookMetadata()
{
    m_bookMetadata.clear();
    
    QList<BookMetadata> books = getUnifiedBookMetadata();
    for (const BookMetadata& book : books) {
        m_bookMetadata[book.code] = qMakePair(book.name, book.chapters);
    }
}

bool BibleDatabase::initialize()
{
    QString dbPath = getDatabasePath();
    
    QFileInfo dbFileInfo(dbPath);
    if (!dbFileInfo.exists()) {
        QString error = QString("Bible database file not found: %1").arg(dbPath);
        qCritical() << error;
        return false;
    }
    
    if (!dbFileInfo.isReadable()) {
        QString error = QString("Bible database file not readable: %1").arg(dbPath);
        qCritical() << error;
        return false;
    }
    
    if (dbFileInfo.size() < 1024) {
        QString error = QString("Bible database file too small, possibly corrupted: %1 (%2 bytes)")
                      .arg(dbPath).arg(dbFileInfo.size());
        qCritical() << error;
        return false;
    }
    
    m_database = QSqlDatabase::addDatabase("QSQLITE", "bible_connection");
    m_database.setDatabaseName(dbPath);
    
    if (!m_database.open()) {
        QString error = QString("Failed to open bible database: %1").arg(m_database.lastError().text());
        qCritical() << error;
        return false;
    }
    
    QSqlQuery pragmaQuery(m_database);
    pragmaQuery.exec("PRAGMA journal_mode = OFF");
    pragmaQuery.exec("PRAGMA synchronous = OFF");
    pragmaQuery.exec("PRAGMA cache_size = -50000");
    pragmaQuery.exec("PRAGMA temp_store = MEMORY");
    pragmaQuery.exec("PRAGMA mmap_size = 268435456");
    pragmaQuery.exec("PRAGMA query_only = 1");
    
    if (!validateDatabaseStructure()) {
        QString error = "Bible database structure validation failed";
        qCritical() << error;
        m_database.close();
        return false;
    }
    
    loadBookMetadata();
    m_initialized = true;
    
    return true;
}

void BibleDatabase::ensureInitialized()
{
    if (m_initialized) {
        return;
    }
    
    if (!m_initializing) {
        m_initializing = true;
        emit initializationStarted();
        
        QFuture<bool> future = QtConcurrent::run([this]() {
            return this->initialize();
        });
        
        QFutureWatcher<bool>* watcher = new QFutureWatcher<bool>(this);
        connect(watcher, &QFutureWatcher<bool>::finished, [this, watcher]() {
            m_initializing = false;
            bool success = watcher->result();
            if (success) {
                emit initializationCompleted(true);
                qDebug() << "Bible database initialized successfully";
            } else {
                emit initializationFailed("Failed to initialize Bible database");
                qWarning() << "Bible database initialization failed";
            }
            watcher->deleteLater();
        });
        watcher->setFuture(future);
    }
}

QString getBookSection(const QString& code)
{
    static QStringList ancientTestament = {"Gn", "Ex", "Lv", "Nb", "Dt", "Jos", "Jg", "Rt", 
                                           "1S", "2S", "1R", "2R", "1Ch", "2Ch", "Esd", "Ne", "Est", "Jb"};
    static QStringList poeticBooks = {"Ps", "Pr", "Qo", "Ct"};
    static QStringList prophets = {"Is", "Jr", "Lm", "Ez", "Dn", "Os", "Jl", "Am", "Ab", "Jon", 
                                   "Mi", "Na", "Ha", "So", "Ag", "Za", "Ml"};
    
    if (ancientTestament.contains(code)) {
        return QCoreApplication::translate("BibleDatabase", "Ancien Testament");
    } else if (poeticBooks.contains(code)) {
        return QCoreApplication::translate("BibleDatabase", "Livres Poétiques");
    } else if (prophets.contains(code)) {
        return QCoreApplication::translate("BibleDatabase", "Prophètes");
    } else {
        return QCoreApplication::translate("BibleDatabase", "Nouveau Testament");
    }
}

QString getBookAbbreviation(const QString& code)
{
    QList<BookMetadata> books = getUnifiedBookMetadata();
    for (const BookMetadata& book : books) {
        if (book.code == code) {
            return book.abbreviation;
        }
    }
    return code;
}

QString BibleDatabase::getBookCodeFromAbbreviation(const QString& abbreviation) const
{
    QList<BookMetadata> books = getUnifiedBookMetadata();
    for (const BookMetadata& book : books) {
        if (book.abbreviation == abbreviation) {
            return book.code;
        }
    }
    return abbreviation;
}

QList<BibleBook*> BibleDatabase::getBooks()
{
    QList<BibleBook*> books;
    
    if (!m_initialized) {
        qWarning() << "Bible database not initialized";
        return books;
    }
    
    QList<BookMetadata> metadata = getUnifiedBookMetadata();
    for (const BookMetadata& bookMeta : metadata) {
        QString section = getBookSection(bookMeta.code);
        BibleBook* book = new BibleBook(bookMeta.code, bookMeta.name, bookMeta.abbreviation, 
                                        bookMeta.chapters, section, this);
        books.append(book);
    }
    
    return books;
}

QList<BibleVerse*> BibleDatabase::getVerses(const QString& bookCode, int chapter)
{
    QList<BibleVerse*> verses;
    
    if (!m_initialized) {
        qWarning() << "Bible database not initialized";
        return verses;
    }
    
    if (bookCode.isEmpty()) {
        qWarning() << "Book code is empty";
        return verses;
    }
    
    if (chapter <= 0) {
        qWarning() << "Invalid chapter number:" << chapter;
        return verses;
    }
    
    QSqlQuery query(m_database);
    query.prepare("SELECT verse, text FROM verses WHERE book = ? AND chapter = ? ORDER BY verse");
    query.addBindValue(bookCode);
    query.addBindValue(QString::number(chapter));
    
    if (!query.exec()) {
        QString error = QString("Failed to query verses: %1").arg(query.lastError().text());
        qWarning() << error;
        return verses;
    }
    
    while (query.next()) {
        int verseNumber = query.value(0).toInt();
        QString text = query.value(1).toString();
        
        BibleVerse* verse = new BibleVerse(bookCode, chapter, verseNumber, text, this);
        verses.append(verse);
    }
    
    return verses;
}

bool BibleDatabase::validateDatabaseStructure()
{
    QSqlQuery query(m_database);
    
    if (!query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='verses'")) {
        qWarning() << "Failed to query sqlite_master:" << query.lastError().text();
        return false;
    }
    
    if (!query.next()) {
        qWarning() << "verses table not found in database";
        return false;
    }
    
    query.clear();
    if (!query.exec("PRAGMA table_info(verses)")) {
        qWarning() << "Failed to get verses table info:" << query.lastError().text();
        return false;
    }
    
    QStringList requiredColumns = {"book", "chapter", "verse", "text"};
    QStringList foundColumns;
    
    while (query.next()) {
        QString columnName = query.value(1).toString().toLower();
        foundColumns.append(columnName);
    }
    
    for (const QString& required : requiredColumns) {
        if (!foundColumns.contains(required)) {
            qWarning() << "Required column missing from verses table:" << required;
            return false;
        }
    }
    
    query.clear();
    if (!query.exec("SELECT COUNT(*) FROM verses LIMIT 1")) {
        qWarning() << "Test query failed:" << query.lastError().text();
        return false;
    }
    
    if (query.next()) {
        int verseCount = query.value(0).toInt();
        qDebug() << "Database validation passed - found" << verseCount << "verses";
    }
    
    return true;
}
