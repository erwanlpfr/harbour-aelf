/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import "pages" as Pages
import "js/DateHelper.js" as DateHelper

ApplicationWindow {
  id: app

  property bool isSunday: new Date().getDay() === 0
  property Component initialPageComponent: isSunday ? massComponent : hourLiturgyComponent

  initialPage: initialPageComponent
  
  Component {
    id: massComponent
    Pages.Mass {}
  }
  
  Component {
    id: hourLiturgyComponent
    Pages.HourLiturgy {}
  }
  
  cover: Qt.resolvedUrl("cover/CoverPage.qml")

  allowedOrientations: defaultAllowedOrientations
}
