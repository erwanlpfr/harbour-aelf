/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef LITURGICALCOLORHELPER_H
#define LITURGICALCOLORHELPER_H

#include <QColor>
#include <QString>

class LiturgicalColorHelper {
public:
    static QColor getColorFromString(const QString& color);
};

#endif // LITURGICALCOLORHELPER_H
