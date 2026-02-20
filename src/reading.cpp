/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "reading.h"

Reading::Reading(QObject* parent)
    : QObject(parent)
{
}

Reading::Reading(
    ReadingType readingType,
    const QString& refrainPsalm,
    const QString& title,
    const QString& editor,
    const QString& author,
    const QString& content,
    const QString& reference,
    const QString& introRead,
    const QString& gospelVerse,
    const QString& refrainReference,
    QObject* parent)
    : QObject(parent)
    , m_readingType(readingType)
    , m_refrainPsalm(refrainPsalm)
    , m_title(title)
    , m_content(content)
    , m_reference(reference)
    , m_introRead(introRead)
    , m_gospelVerse(gospelVerse)
    , m_refrainReference(refrainReference)
    , m_editor(editor)
    , m_author(author)
{
}

#define READING_GETTER(Type, name, member) \
    Type Reading::name() const { return member; }

READING_GETTER(Reading::ReadingType, readingType, m_readingType)
READING_GETTER(QString, refrainPsalm, m_refrainPsalm)
READING_GETTER(QString, title, m_title)
READING_GETTER(QString, content, m_content)
READING_GETTER(QString, reference, m_reference)
READING_GETTER(QString, introRead, m_introRead)
READING_GETTER(QString, gospelVerse, m_gospelVerse)
READING_GETTER(QString, refrainReference, m_refrainReference)
READING_GETTER(QString, editor, m_editor)
READING_GETTER(QString, author, m_author)

#undef READING_GETTER
