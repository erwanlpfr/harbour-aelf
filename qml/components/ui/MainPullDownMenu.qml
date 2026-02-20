/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0

PullDownMenu {
  MenuItem {
    text: qsTr("Messe")
    onClicked: pageStack.replace(Qt.resolvedUrl("../../pages/Mass.qml"))
  }

  MenuItem {
    text: qsTr("Liturgie des Heures")
    onClicked: pageStack.replace(Qt.resolvedUrl("../../pages/HourLiturgy.qml"))
  }

  MenuItem {
    text: qsTr("Bible")
    onClicked: pageStack.push(Qt.resolvedUrl("../../pages/Bible.qml"))
  }

  MenuItem {
    text: qsTr("Informations")
    onClicked: pageStack.replace(Qt.resolvedUrl("../../pages/Information.qml"))
  }

  MenuItem {
    text: qsTr("À propos")
    onClicked: pageStack.push(Qt.resolvedUrl("../../pages/About.qml"))
  }

  MenuItem {
    text: qsTr("Paramètres")
    onClicked: pageStack.push(Qt.resolvedUrl("../../pages/Settings.qml"))
  }
}
