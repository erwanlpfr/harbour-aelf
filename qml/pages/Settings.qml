/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import "../components/inputs" as Inputs
import ".." as Root

Page {
  id: page
  
  // Properties to prevent DialogHeader null access errors
  property bool backIndicatorDown: false
  property bool forwardIndicatorDown: false

  SilicaFlickable {
    anchors.fill: parent

    Column {
      anchors.fill: parent

      PageHeader {
        title: qsTr("Paramètres")
      }

      Inputs.ZoneCombobox {
        id: zoneCombobox
        value: Root.AppSettings.currentZone
        onValueChanged: Root.AppSettings.setZone(value)
      }
    }
  }
}
