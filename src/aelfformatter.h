/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef AELFFORMATTER_H
#define AELFFORMATTER_H

#include <QString>
#include "aelftexts.h"

class QJsonObject;

class AelfFormatter {
public:
    static QString processHtml(const QString& html);
    static QString stripHtmlTags(const QString& html);
    static QString addAntienneBefore(const QString& content);
    static QString capitalize(const QString& text);
    static QString appendReponsIfPresent(const QString& content, const QJsonObject& obj, const QString& key);
};

#endif // AELFFORMATTER_H
