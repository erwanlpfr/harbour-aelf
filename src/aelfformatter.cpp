/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "aelfformatter.h"
#include <QRegularExpression>
#include <QCoreApplication>
#include <QJsonObject>

using namespace AelfLiturgy;
using namespace HtmlUtils;

QString AelfFormatter::processHtml(const QString& html)
{
    QString result = html;

    result.replace(GLORIA_PATRI_SHORT, AelfTexts::gloriaPatri());

    for (const QString& marker : LITURGY_MARKERS) {
        result.replace(marker, accent(marker));
    }

    static QRegularExpression verseRe(
        R"(<span\s+class="verse_number">(\d+)</span>)",
        QRegularExpression::CaseInsensitiveOption
    );
    result.replace(verseRe, highlight("\\1"));

    return result;
}

QString AelfFormatter::stripHtmlTags(const QString& html)
{
    QRegularExpression re("<[^>]*>");
    return QString(html).remove(re);
}

QString AelfFormatter::formatAntienne(const QString& content, AntiennePosition pos)
{
    if (content.isEmpty()) {
        return QString();
    }
    QString cleanContent = content;
    cleanContent.replace("<p>", "");
    cleanContent.replace("</p>", "");
    cleanContent = cleanContent.trimmed();

    QString text = accent(AelfTexts::antienneLabel()) + " " + cleanContent;
    return pos == AntiennePosition::After ? "<br><p><i>" + text + "</i></p>" : text;
}

QString AelfFormatter::capitalize(const QString& text)
{
    if (text.isNull() || text.length() <= 1) {
        return QString();
    }
    return text.at(0).toUpper() + text.mid(1).toLower();
}

QString AelfFormatter::appendReponsIfPresent(const QString& content, const QJsonObject& obj, const QString& key)
{
    QString repons = obj.value(key).toString();
    return repons.isEmpty() ? content : content + AelfTexts::reponsMarker() + repons;
}
