/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef AELFTEXTS_H
#define AELFTEXTS_H

#include <QString>
#include <QStringList>
#include "htmlutils.h"

namespace AelfLiturgy {
    static const auto GLORIA_PATRI_SHORT = QStringLiteral("Gloire au Père,..");
    inline QString reponsBlock(const QString& text) { return "<br/><br/>" + HtmlUtils::accent(text) + "<br/>"; }
    static const QStringList LITURGY_MARKERS = {"V/", "R/", "*", "+"};
}

namespace AelfTexts {
    QString gloriaPatri();
    QString notrePere();
    QString oraisonSuffix();
    QString reponsMarker();
    QString antienneLabel();
    QString paroleDeDieu();
    QString intercession();
    QString notrePereLabel();
    QString oraisonLabel();
}

#endif // AELFTEXTS_H
