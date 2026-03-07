/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef HTMLUTILS_H
#define HTMLUTILS_H

#include <QString>

namespace HtmlUtils {
    inline QString p(const QString& text) { return "<p>" + text + "</p>"; }
    inline QString highlight(const QString& text) { return "<small><b><font color=\"{{HIGHLIGHT_COLOR}}\">" + text + "</font></b></small> "; }
    inline QString accent(const QString& text) { return "<font color=\"{{ACCENT_COLOR}}\">" + text + "</font>"; }
    inline QString spacer() { return QStringLiteral("<p class=\"spacer\"><br></p>"); }
}

#endif // HTMLUTILS_H
