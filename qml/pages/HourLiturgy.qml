/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import harbour.org.aelf 1.0
import "../components/headers" as Headers
import "../components/inputs" as Inputs
import "../components/ui" as UI
import "../components/layout" as Layout
import "../js/DateHelper.js" as DateHelper
import "../js/StringHelper.js" as StringHelper
import "../modules/Opal/Tabs" as Tabs
import ".." as Root

Page {
  id: page

  allowedOrientations: Orientation.All
  highContrast: true
  forwardNavigation: true
  
  // Properties to prevent DialogHeader null access errors
  property bool backIndicatorDown: false
  property bool forwardIndicatorDown: false

  property var _pickerPage: null

  onStatusChanged: {
    if (status === PageStatus.Active) {
      _pickerPage = pageStack.pushAttached(
            "../components/inputs/HourTypePicker.qml",
            {"selectedType": hourLiturgyModel.type})
      _pickerPage.typeSelected.connect(function(hourType) {
        hourLiturgyModel.type = hourType
      })
    }
  }

  Connections {
    target: hourLiturgyModel
    onTypeChanged: {
      if (_pickerPage) {
        _pickerPage.selectedType = hourLiturgyModel.type
      }
    }
  }

  HourLiturgyModel {
    id: hourLiturgyModel
    date: new Date()
    zone: Root.AppSettings.currentZone
    type: DateHelper.getHourTypeForTime(HourLiturgy)
  }

  SilicaFlickable {
    id: mainFlickable
    anchors.fill: parent

    UI.MainPullDownMenu {}

    Headers.PageHeaderWithDate {
      id: pageHeader
      title: qsTr("Liturgie des Heures")
      description: (hourLiturgyModel.hourLiturgy ? StringHelper.capitalizeFirstLetter(hourLiturgyModel.hourLiturgy.type) : qsTr(
                                                     "Chargement..."))

      onDateChanged: {
        hourLiturgyModel.date = date
      }
    }

    BusyLabel {
      visible: hourLiturgyModel.loading
      running: true
      text: qsTr("Récupération de la liturgie...")
      anchors.centerIn: parent
    }

    Loader {
      active: !hourLiturgyModel.loading && hourLiturgyModel.hourLiturgy
              && hourLiturgyModel.hourLiturgy.readingsModel
      anchors {
        top: pageHeader.bottom
        left: parent.left
        right: parent.right
        bottom: parent.bottom
      }
      sourceComponent: Component {
        Tabs.TabView {
          id: tabs
          anchors.fill: parent
          currentIndex: 0
          tabBarPosition: Qt.AlignTop
          model: hourLiturgyModel.hourLiturgy.readingsModel
          
          // Context properties for Opal Tab components
          property Item _ctxPage: page
          property Item _ctxTabContainer: parent
        }
      }
    }

    ViewPlaceholder {
      enabled: !hourLiturgyModel.loading && !hourLiturgyModel.hourLiturgy
      text: qsTr("Aucune liturgie disponible")
      hintText: qsTr("Tirez vers le bas pour changer la date ou vérifier votre connexion")
    }
  }
}
