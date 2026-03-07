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
    contentHeight: contentColumn.height

    Column {
      id: contentColumn
      width: parent.width

      PageHeader {
        title: qsTr("Paramètres")
      }

      SectionHeader {
        text: qsTr("Liturgie")
      }

      Inputs.ZoneCombobox {
        id: zoneCombobox
        value: Root.AppSettings.currentZone
        onValueChanged: Root.AppSettings.setZone(value)
      }

      ComboBox {
        id: startPageCombobox
        label: qsTr("Page de démarrage")
        currentIndex: {
          switch (Root.AppSettings.currentStartPage) {
            case "mass": return 1
            case "hours": return 2
            default: return 0
          }
        }

        menu: ContextMenu {
          MenuItem { text: qsTr("Automatique (selon le jour)") }
          MenuItem { text: qsTr("Messe") }
          MenuItem { text: qsTr("Liturgie des Heures") }
        }

        onCurrentIndexChanged: {
          var values = ["auto", "mass", "hours"]
          if (currentIndex >= 0 && currentIndex < values.length) {
            Root.AppSettings.setStartPage(values[currentIndex])
          }
        }
      }

      SectionHeader {
        text: qsTr("Affichage")
      }

      Slider {
        id: fontScaleSlider
        width: parent.width
        minimumValue: 0.8
        maximumValue: 1.6
        stepSize: 0.05
        value: Root.AppSettings.currentFontScale
        label: qsTr("Taille de police")
        valueText: Math.round(sliderValue * 100) + "%"

        onSliderValueChanged: {
          Root.AppSettings.setFontScale(sliderValue)
        }
      }

      Label {
        x: Theme.horizontalPageMargin
        width: parent.width - 2 * Theme.horizontalPageMargin
        text: qsTr("Exemple de texte avec la taille actuelle")
        wrapMode: Text.WordWrap
        font.pixelSize: Root.AppSettings.scaledFont(Theme.fontSizeMedium)
        color: Theme.primaryColor
      }
    }
  }
}
