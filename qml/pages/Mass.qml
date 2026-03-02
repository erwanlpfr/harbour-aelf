/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import harbour.org.aelf 1.0
import "../components/headers" as Headers
import "../components/ui" as UI
import "../modules/Opal/Tabs" as Tabs
import ".." as Root

Page {
  id: page

  allowedOrientations: Orientation.All
  highContrast: true
  forwardNavigation: massModel.massNames.length > 1
  
  // Properties to prevent DialogHeader null access errors
  property bool backIndicatorDown: false
  property bool forwardIndicatorDown: false

  onStatusChanged: {
    if (status === PageStatus.Active && massModel.massNames.length > 1) {
      var picker = pageStack.pushAttached(
            "../components/inputs/MassPicker.qml",
            {"massNames": massModel.massNames, "selectedIndex": massModel.currentMassIndex})
      picker.massSelected.connect(function(index) {
        massModel.currentMassIndex = index
      })
    }
  }

  MassModel {
    id: massModel
    date: new Date()
    zone: Root.AppSettings.currentZone
  }

  SilicaFlickable {
    anchors.fill: parent

    UI.MainPullDownMenu {}

    Headers.PageHeaderWithDate {
      id: pageHeader
      title: qsTr("Messe")
      description: (massModel.currentMass ? massModel.currentMass.name : qsTr(
                                              "Chargement..."))

      onDateChanged: {
        massModel.date = date
      }
    }

    BusyLabel {
      visible: massModel.loading
      running: true
      text: qsTr("Récupération de la messe...")
      anchors.centerIn: parent
    }

    Loader {
      active: !massModel.loading && massModel.currentMass
              && massModel.currentMass.readingsModel
      anchors {
        top: pageHeader.bottom
        left: parent.left
        right: parent.right
        bottom: parent.bottom
      }
      sourceComponent: Component {
        Tabs.TabView {
          anchors.fill: parent
          currentIndex: 0
          tabBarPosition: Qt.AlignTop
          model: massModel.currentMass.readingsModel
          
          // Context properties for Opal Tab components
          property Item _ctxPage: page
          property Item _ctxTabContainer: parent
        }
      }
    }

    ViewPlaceholder {
      enabled: !massModel.loading && !massModel.currentMass
      text: qsTr("Aucune messe disponible")
      hintText: qsTr("Tirez vers le bas pour changer la date ou vérifier votre connexion")
    }
  }
}
