/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import harbour.org.aelf 1.0
import "../js/DateHelper.js" as DateHelper
import ".." as Root

CoverBackground {
  id: cover

  property string currentHour: DateHelper.getCurrentHourName()

  InformationModel {
    id: coverInfoModel
    date: new Date()
    zone: Root.AppSettings.currentZone
  }

  Timer {
    interval: 60 * 60 * 1000
    running: cover.status === Cover.Active
    repeat: true
    onTriggered: {
      coverInfoModel.date = new Date()
    }
  }

  function refreshCover() {
    currentHour = DateHelper.getCurrentHourName()
    var now = new Date()
    coverInfoModel.date = now
    coverInfoModel.loadData()
  }

  onStatusChanged: {
    if (status === Cover.Active) {
      var now = new Date()
      if (now.toDateString() !== coverInfoModel.date.toDateString()) {
        refreshCover()
      }
    }
  }

  Component.onCompleted: {
    if (status === Cover.Active) {
      refreshCover()
    }
  }

  Rectangle {
    id: colorBar
    anchors {
      left: parent.left
      top: parent.top
      bottom: parent.bottom
    }
    width: Theme.paddingSmall
    color: coverInfoModel.information ? coverInfoModel.information.color : Theme.highlightColor
  }

  Column {
    anchors {
      left: colorBar.right
      right: parent.right
      verticalCenter: parent.verticalCenter
      margins: Theme.paddingMedium
    }
    spacing: Theme.paddingSmall

    Label {
      width: parent.width
      text: qsTr("AELF")
      font.pixelSize: Theme.fontSizeSmall
      color: Theme.secondaryColor
    }

    Label {
      width: parent.width
      text: cover.currentHour
      font.pixelSize: Theme.fontSizeMedium
      font.bold: true
      color: Theme.highlightColor
    }

    Label {
      width: parent.width
      text: coverInfoModel.information ? coverInfoModel.information.liturgicalDayName : ""
      font.pixelSize: Theme.fontSizeExtraSmall
      color: Theme.primaryColor
      wrapMode: Text.WordWrap
      maximumLineCount: 2
      elide: Text.ElideRight
    }
  }

  CoverActionList {
    CoverAction {
      iconSource: "image://theme/icon-cover-new"
      onTriggered: {
        app.activate()
        pageStack.clear()
        pageStack.push(Qt.resolvedUrl("../pages/Mass.qml"))
      }
    }
    CoverAction {
      iconSource: "image://theme/icon-cover-timer"
      onTriggered: {
        app.activate()
        pageStack.clear()
        pageStack.push(Qt.resolvedUrl("../pages/HourLiturgy.qml"))
      }
    }
  }
}
