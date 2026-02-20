/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "aelfformatter.h"
#include <QRegularExpression>
#include <QCoreApplication>
#include <QJsonObject>

QString AelfFormatter::processHtml(const QString& html)
{
    QString result = html;
    
    static const QStringList markers = {"V/", "R/", "*", "+"};
    for (const QString& marker : markers) {
        result.replace(marker, QStringLiteral("<font color=\"{{ACCENT_COLOR}}\">%1</font>").arg(marker));
    }
    
    static QRegularExpression verseRe(
        R"(<span\s+class="verse_number">(\d+)</span>)",
        QRegularExpression::CaseInsensitiveOption
    );
    result.replace(verseRe, QStringLiteral("<small><b><font color=\"{{HIGHLIGHT_COLOR}}\">\\1</font></b></small> "));
    
    return result;
}

QString AelfFormatter::stripHtmlTags(const QString& html)
{
    QRegularExpression re("<[^>]*>");
    return QString(html).remove(re);
}

QString AelfFormatter::addAntienneBefore(const QString& content)
{
    if (content.isEmpty()) {
        return QString();
    }
    QString cleanContent = content;
    cleanContent.replace("<p>", "");
    cleanContent.replace("</p>", "");
    cleanContent = cleanContent.trimmed();
    
    return "<font color=\"{{ACCENT_COLOR}}\">" + QCoreApplication::translate("AelfFormatter", "Antienne:") + "</font> " + cleanContent;
}

QString AelfFormatter::capitalize(const QString& text)
{
    if (text.isNull() || text.length() <= 1) {
        return QString();
    }
    return text.at(0).toUpper() + text.mid(1).toLower();
}

QString AelfFormatter::gloriaPatri()
{
    return "<p>" + QCoreApplication::translate("AelfFormatter", "Gloire au Père,...") + "</p>";
}

QString AelfFormatter::notrePereText()
{
    return QCoreApplication::translate("AelfFormatter",
        "Notre Père, qui es aux cieux, <br>"
        "que ton nom soit sanctifié,<br>"
        "que ton règne vienne,<br>"
        "que ta volonté soit faite sur la terre comme au ciel.<br>"
        "Donne-nous aujourd'hui notre pain de ce jour.<br>"
        "Pardonne-nous nos offenses,<br>"
        "comme nous pardonnons aussi à ceux qui nous ont offensés.<br>"
        "Et ne nous laisse pas entrer en tentation<br>"
        "mais délivre-nous du Mal.<br><br>"
        "Amen"
    );
}

QString AelfFormatter::oraisonSuffix()
{
    return "<p class=\"spacer\"><br></p>" +
        QCoreApplication::translate("AelfFormatter",
            "Que le Seigneur nous bénisse, qu'il nous garde de tout mal, "
            "et nous conduise à la vie éternelle.<br>Amen."
        );
}

QString AelfFormatter::reponsMarker()
{
    return "<br/><br/><font color=\"{{ACCENT_COLOR}}\">" + QCoreApplication::translate("AelfFormatter", "Répons") + "</font><br/>";
}

QString AelfFormatter::appendReponsIfPresent(const QString& content, const QJsonObject& obj, const QString& key)
{
    QString repons = obj.value(key).toString();
    return repons.isEmpty() ? content : content + reponsMarker() + repons;
}

