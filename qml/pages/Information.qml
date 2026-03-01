/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import harbour.org.aelf 1.0
import "../components/headers" as Headers
import "../components/ui" as UI
import ".." as Root

Page {
  id: page

  allowedOrientations: Orientation.All
  
  // Properties to prevent DialogHeader null access errors
  property bool backIndicatorDown: false
  property bool forwardIndicatorDown: false

  InformationModel {
    id: informationModel
    date: new Date()
    zone: Root.AppSettings.currentZone
  }

  SilicaFlickable {
    id: flickable
    anchors.fill: parent
    contentHeight: column.height + Theme.paddingLarge

    VerticalScrollDecorator {}

    UI.MainPullDownMenu {}

    Column {
      id: column
      width: parent.width

        Headers.PageHeaderWithDate {
          id: pageHeader
          title: qsTr("Informations")

          onDateChanged: {
            informationModel.date = date
          }
        }

        Item {
          width: parent.width
          height: Theme.itemSizeMedium
          visible: informationModel.loading

          BusyIndicator {
            anchors.centerIn: parent
            size: BusyIndicatorSize.Medium
            running: informationModel.loading
          }
        }

        Loader {
          width: parent.width
          active: !informationModel.loading && !informationModel.empty
                  && informationModel.information
          sourceComponent: Component {
            Column {
              width: parent.width

              Item {
                id: contentItem
                width: parent.width
                height: contentColumn.height + Theme.paddingLarge * 2

                Rectangle {
                  id: colorBar
                  anchors {
                    left: parent.left
                    top: parent.top
                    bottom: parent.bottom
                    topMargin: Theme.paddingMedium
                    bottomMargin: Theme.paddingMedium
                  }
                  width: Theme.paddingSmall
                  radius: width / 2
                  color: informationModel.information.color
                }

                Column {
                  id: contentColumn
                  anchors {
                    left: colorBar.right
                    right: parent.right
                    top: parent.top
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                    topMargin: Theme.paddingMedium
                  }
                  spacing: Theme.paddingMedium

                  Label {
                    width: parent.width
                    text: informationModel.information.liturgicalDayName
                    font.pixelSize: Root.AppSettings.scaledFont(Theme.fontSizeExtraLarge)
                    color: Theme.highlightColor
                    wrapMode: Text.WordWrap
                  }

                  Label {
                    width: parent.width
                    visible: informationModel.information.degree
                    text: informationModel.information.degree
                    font.pixelSize: Root.AppSettings.scaledFont(Theme.fontSizeMedium)
                    font.italic: true
                    color: Theme.secondaryHighlightColor
                    wrapMode: Text.WordWrap
                  }
                }
              }

              SectionHeader {
                text: qsTr("Détails")
              }

              DetailItem {
                visible: informationModel.information.liturgicalTime
                label: qsTr("Temps liturgique")
                value: informationModel.information.liturgicalTime
              }

              DetailItem {
                visible: informationModel.information.holiday
                label: qsTr("Célébration")
                value: informationModel.information.holiday
              }

              DetailItem {
                visible: informationModel.information.liturgicalZone
                label: qsTr("Zone liturgique")
                value: informationModel.information.liturgicalZone
              }

              DetailItem {
                label: qsTr("Jour")
                value: informationModel.information.day
              }

              DetailItem {
                label: qsTr("Semaine")
                value: informationModel.information.week
              }

              DetailItem {
                label: qsTr("Année liturgique")
                value: informationModel.information.year
              }

              SectionHeader {
                text: qsTr("Résumé du jour")
                visible: informationModel.information.line1
                         || informationModel.information.line2
                         || informationModel.information.line3
              }

              Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                visible: informationModel.information.line1
                text: informationModel.information.line1
                font.pixelSize: Root.AppSettings.scaledFont(Theme.fontSizeSmall)
                color: Theme.primaryColor
                wrapMode: Text.WordWrap
              }

              Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                visible: informationModel.information.line2
                text: informationModel.information.line2
                font.pixelSize: Root.AppSettings.scaledFont(Theme.fontSizeSmall)
                color: Theme.secondaryColor
                wrapMode: Text.WordWrap
              }

              Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                visible: informationModel.information.line3
                text: informationModel.information.line3
                font.pixelSize: Root.AppSettings.scaledFont(Theme.fontSizeSmall)
                color: Theme.secondaryColor
                wrapMode: Text.WordWrap
              }
            }
          }
        }

        Item {
          width: 1
          height: Theme.paddingLarge
        }
      }

    ViewPlaceholder {
      enabled: !informationModel.loading && informationModel.empty
      text: qsTr("Aucune information disponible")
      hintText: qsTr("Tirez vers le bas pour changer la date ou vérifier votre connexion")
    }
  }
}
