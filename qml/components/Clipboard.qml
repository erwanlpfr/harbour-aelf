/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Nemo.DBus 2.0

DBusInterface {
    service: "org.sailfishos.clipboard"
    path: "/"
    iface: "org.sailfishos.clipboard"
    bus: DBus.SessionBus
    
    function setText(text) {
        call("SetText", [text])
    }
}
