/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import "pages" as Pages
import "." as Root

ApplicationWindow {
  id: app

  property Component initialPageComponent: {
    var startPage = Root.AppSettings.currentStartPage
    if (startPage === "mass") return massComponent
    if (startPage === "hours") return hourLiturgyComponent
    return new Date().getDay() === 0 ? massComponent : hourLiturgyComponent
  }

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
