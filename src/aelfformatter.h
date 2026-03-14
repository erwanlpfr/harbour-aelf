/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef AELFFORMATTER_H
#define AELFFORMATTER_H

#include "aelftexts.h"
#include <QString>

class QJsonObject;

enum class AntiennePosition { Before, After };

class AelfFormatter {
  public:
    static QString processHtml(const QString& html);
    static QString stripHtmlTags(const QString& html);
    static QString formatAntienne(const QString& content, AntiennePosition pos);
    static QString capitalize(const QString& text);
    static QString appendReponsIfPresent(const QString& content, const QJsonObject& obj,
                                         const QString& key);
};

#endif // AELFFORMATTER_H
