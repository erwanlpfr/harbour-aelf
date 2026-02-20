/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "bibleversesmodel.h"
#include "bibleverse.h"
#include "bibledatabase.h"
#include "errorhandler.h"
#include <QDebug>

BibleVersesModel::BibleVersesModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_chapter(0)
{
    m_roles[VerseNumberRole] = "verseNumber";
    m_roles[TextRole] = "verseText";
}

BibleVersesModel::~BibleVersesModel()
{
    qDeleteAll(m_verses);
}

int BibleVersesModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_verses.count();
}

QVariant BibleVersesModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_verses.count()) {
        return QVariant();
    }

    BibleVerse* verse = m_verses.at(index.row());

    switch (role) {
    case VerseNumberRole:
        return verse->verseNumber();
    case TextRole:
        return verse->text();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> BibleVersesModel::roleNames() const
{
    return m_roles;
}

void BibleVersesModel::setBookCode(const QString& bookCode)
{
    if (m_bookCode != bookCode) {
        m_bookCode = bookCode;
        emit bookCodeChanged();
    }
}

void BibleVersesModel::setChapter(int chapter)
{
    if (m_chapter != chapter) {
        m_chapter = chapter;
        emit chapterChanged();
    }
}

void BibleVersesModel::loadVerses()
{
    beginResetModel();
    
    qDeleteAll(m_verses);
    m_verses.clear();
    
    if (m_bookCode.isEmpty() || m_chapter <= 0) {
        endResetModel();
        emit countChanged();
        return;
    }
    
    BibleDatabase* db = BibleDatabase::instance();
    db->ensureInitialized();
    
    if (!db->isInitialized()) {
        endResetModel();
        emit countChanged();
        return;
    }
    
    m_verses = db->getVerses(m_bookCode, m_chapter);
    
    endResetModel();
    
    emit countChanged();
}
