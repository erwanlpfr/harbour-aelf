/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

.pragma library

function formatVerseReference(bookName, chapter, verseNumber) {
    return bookName + " " + chapter + ":" + verseNumber
}

function formatVerseText(bookName, chapter, verseNumber, verseText) {
    return formatVerseReference(bookName, chapter, verseNumber) + "\n" + verseText
}
