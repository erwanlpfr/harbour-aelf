/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "bibleverse.h"

BibleVerse::BibleVerse(const QString& bookCode, int chapter,
                       int verseNumber, const QString& text,
                       QObject* parent)
    : QObject(parent)
    , m_bookCode(bookCode)
    , m_chapter(chapter)
    , m_verseNumber(verseNumber)
    , m_text(text)
{
}
