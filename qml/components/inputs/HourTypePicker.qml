/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.2
import Sailfish.Silica 1.0
import harbour.org.aelf 1.0
import "../../js/StringHelper.js" as StringHelper

Page {
  id: page

  property int selectedType: HourLiturgy.Vespers

  signal typeSelected(int hourType)

  SilicaFlickable {
    anchors.fill: parent
    contentHeight: column.height

    VerticalScrollDecorator {}

    Column {
      id: column
      width: parent.width

      PageHeader {
        title: qsTr("Liturgie des Heures")
      }

      TextSwitch {
        text: StringHelper.toTitleCase(qsTr("lectures"))
        description: qsTr("Office des lectures")
        checked: page.selectedType === HourLiturgy.Lectures
        automaticCheck: false
        onClicked: {
          page.selectedType = HourLiturgy.Lectures
          page.typeSelected(HourLiturgy.Lectures)
          pageStack.navigateBack()
        }
      }

      TextSwitch {
        text: StringHelper.toTitleCase(qsTr("lauds"))
        description: qsTr("Prière du matin")
        checked: page.selectedType === HourLiturgy.Lauds
        automaticCheck: false
        onClicked: {
          page.selectedType = HourLiturgy.Lauds
          page.typeSelected(HourLiturgy.Lauds)
          pageStack.navigateBack()
        }
      }

      TextSwitch {
        text: StringHelper.toTitleCase(qsTr("terce"))
        description: qsTr("Prière du milieu de la matinée")
        checked: page.selectedType === HourLiturgy.Terce
        automaticCheck: false
        onClicked: {
          page.selectedType = HourLiturgy.Terce
          page.typeSelected(HourLiturgy.Terce)
          pageStack.navigateBack()
        }
      }

      TextSwitch {
        text: StringHelper.toTitleCase(qsTr("sext"))
        description: qsTr("Prière de midi")
        checked: page.selectedType === HourLiturgy.Sext
        automaticCheck: false
        onClicked: {
          page.selectedType = HourLiturgy.Sext
          page.typeSelected(HourLiturgy.Sext)
          pageStack.navigateBack()
        }
      }

      TextSwitch {
        text: StringHelper.toTitleCase(qsTr("none"))
        description: qsTr("Prière de l'après-midi")
        checked: page.selectedType === HourLiturgy.None
        automaticCheck: false
        onClicked: {
          page.selectedType = HourLiturgy.None
          page.typeSelected(HourLiturgy.None)
          pageStack.navigateBack()
        }
      }

      TextSwitch {
        text: StringHelper.toTitleCase(qsTr("vespers"))
        description: qsTr("Prière du soir")
        checked: page.selectedType === HourLiturgy.Vespers
        automaticCheck: false
        onClicked: {
          page.selectedType = HourLiturgy.Vespers
          page.typeSelected(HourLiturgy.Vespers)
          pageStack.navigateBack()
        }
      }

      TextSwitch {
        text: StringHelper.toTitleCase(qsTr("compline"))
        description: qsTr("Prière de la nuit")
        checked: page.selectedType === HourLiturgy.Compline
        automaticCheck: false
        onClicked: {
          page.selectedType = HourLiturgy.Compline
          page.typeSelected(HourLiturgy.Compline)
          pageStack.navigateBack()
        }
      }
    }
  }
}
