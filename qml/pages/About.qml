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
    description: qsTr("Application liturgique fournissant les messes quotidiennes, les heures et les lectures pour la liturgie catholique, basée sur les données publiques d'aelf.org.")
    authors: [qsTr("2026-%1 harbour-aelf Contributors").arg((new Date()).getFullYear())]
    licenses: A.License { spdxId: "GPL-3.0-or-later" }
    sourcesUrl: "https://github.com/erwanlpfr/harbour-aelf"
    
    extraSections: [
        A.InfoSection {
            title: qsTr("Informations")
            text: qsTr("Cette application n'est ni affiliée ni autorisée par l'AELF (Association Épiscopale Liturgique pour les pays Francophones). Elle utilise l'API publique d'aelf.org.

Les textes liturgiques sont la propriété de l'AELF. Le logo et le nom AELF sont utilisés à titre informatif uniquement.

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
