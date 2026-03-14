/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "biblebook.h"

BibleBook::BibleBook(const QString& code, const QString& name, const QString& abbreviation,
                     int chapterCount, const QString& section, QObject* parent)
    : QObject(parent), m_code(code), m_name(name), m_abbreviation(abbreviation),
      m_chapterCount(chapterCount), m_section(section) {
}
