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
    }

    readonly property string currentZone: settings.zone

    function setZone(newZone) {
        settings.zone = newZone
    }
}
