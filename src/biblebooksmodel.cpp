/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "biblebooksmodel.h"
#include "biblebook.h"
#include "bibledatabase.h"
#include <QDebug>

BibleBooksModel::BibleBooksModel(QObject* parent)
    : QAbstractListModel(parent)
{
    m_roles[CodeRole] = "code";
    m_roles[NameRole] = "name";
    m_roles[AbbreviationRole] = "abbreviation";
    m_roles[ChaptersRole] = "chapters";
    m_roles[SectionRole] = "section";
}

BibleBooksModel::~BibleBooksModel()
{
    qDeleteAll(m_allBooks);
}

int BibleBooksModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_filteredBooks.count();
}

QVariant BibleBooksModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_filteredBooks.count()) {
        return QVariant();
    }

    BibleBook* book = m_filteredBooks.at(index.row());

    switch (role) {
    case CodeRole:
        return book->code();
    case NameRole:
        return book->name();
    case AbbreviationRole:
        return book->abbreviation();
    case ChaptersRole:
        return book->chapterCount();
    case SectionRole:
        return book->section();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> BibleBooksModel::roleNames() const
{
    return m_roles;
}

void BibleBooksModel::setSection(const QString& section)
{
    if (m_section != section) {
        m_section = section;
        filterBooks();
        emit sectionChanged();
    }
}

void BibleBooksModel::loadBooks()
{
    beginResetModel();
    
    qDeleteAll(m_allBooks);
    m_allBooks.clear();
    m_filteredBooks.clear();
    
    BibleDatabase* db = BibleDatabase::instance();
    if (!db->isInitialized()) {
        if (!db->initialize()) {
            qWarning() << "Failed to initialize Bible database";
            endResetModel();
            return;
        }
    }
    
    m_allBooks = db->getBooks();
    filterBooks();
    
    endResetModel();
}

void BibleBooksModel::filterBooks()
{
    m_filteredBooks.clear();
    
    if (m_section.isEmpty()) {
        m_filteredBooks = m_allBooks;
    } else {
        for (BibleBook* book : m_allBooks) {
            if (book->section() == m_section) {
                m_filteredBooks.append(book);
            }
        }
    }
}
