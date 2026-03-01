/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import "../modules/Opal/About" as A
import "../components/ui" as UI

A.AboutPageBase {
    id: root
    allowedOrientations: Orientation.All
    appName: "aelf"
    appIcon: "image://theme/harbour-aelf"
    appVersion: "1.1.0"
    description: qsTr("AELF est une application liturgique fournissant les messes quotidiennes, les heures et les lectures pour la liturgie catholique.")
    authors: [qsTr("2026-%1 AELF Contributors").arg((new Date()).getFullYear())]
    licenses: A.License { spdxId: "GPL-3.0-or-later" }
    sourcesUrl: "https://github.com/erwanlpfr/harbour-aelf"
    
    extraSections: [
        A.InfoSection {
            title: qsTr("Informations")
            text: qsTr("L'application Harbour AELF est développée bénévolement avec le soutien d'AELF (www.aelf.org), l'Association Épiscopale pour la Liturgie Francophone.

Textes liturgiques, logo et nom reproduits avec l'aimable autorisation d'AELF. Tous droits réservés. AELF n'est pas responsable de cette application.

Pour plus d'informations sur cette application, contacter le mainteneur de https://github.com/erwanlpfr/harbour-aelf")
            enabled: true
        },
        A.InfoSection {
            title: qsTr("À venir")
            text: qsTr("- Liturgie hors ligne sur plusieurs périodes")
            enabled: true
        }
    ]
    
    // Properties to prevent DialogHeader null access errors
    property bool backIndicatorDown: false
    property bool forwardIndicatorDown: false
    
    UI.MainPullDownMenu {}
}
