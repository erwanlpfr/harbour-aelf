/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

pragma Singleton
import QtQuick 2.6
import Nemo.Configuration 1.0

QtObject {
    id: appSettings

    property ConfigurationGroup settings: ConfigurationGroup {
        path: "/apps/harbour-aelf"

        property string zone: "france"
        property string fontScale: "1.0"
        property string startPage: "auto"
    }

    readonly property string currentZone: settings.zone
    readonly property string currentStartPage: settings.startPage
    readonly property real currentFontScale: {
        var scale = parseFloat(settings.fontScale)
        if (isNaN(scale) || scale < 0.8 || scale > 1.6) return 1.0
        return scale
    }

    function setZone(newZone) {
        settings.zone = newZone
    }

    function scaledFont(baseSize) {
        return Math.round(baseSize * currentFontScale)
    }

    function setFontScale(newScale) {
        var clamped = Math.max(0.8, Math.min(1.6, newScale))
        settings.fontScale = clamped.toFixed(2)
    }

    function setStartPage(newStartPage) {
        settings.startPage = newStartPage
    }
}
