/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "liturgicalcolorhelper.h"

QColor LiturgicalColorHelper::getColorFromString(const QString& color)
{
    if (color == "blanc")
        return QColor(255, 255, 255);
    else if (color == "vert")
        return QColor(0, 128, 0);
    else if (color == "rouge")
        return QColor(255, 0, 0);
    else if (color == "violet")
        return QColor(128, 0, 128);
    else if (color == "rose")
        return QColor(255, 192, 203);
    else if (color == "noir")
        return QColor(0, 0, 0);
    else
        return QColor(128, 128, 128);
}
