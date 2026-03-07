/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import "../../js/DateHelper.js" as DateHelper

MouseArea {
  id: dateDatePicker

  property date date: new Date()

  height: Theme.itemSizeLarge

  onClicked: {
    var dialog = pageStack.push(pickerComponent, {
                                  "date": dateDatePicker.date
                                })

    dialog.accepted.connect(function () {
      dateDatePicker.date = dialog.date
    })
  }

  Label {
    text: DateHelper.formatRelativeDate(dateDatePicker.date)
    color: dateDatePicker.pressed ? Theme.highlightColor : Theme.secondaryColor
    truncationMode: TruncationMode.Fade
    padding: Theme.paddingLarge
    anchors {
      verticalCenter: parent.verticalCenter
    }
    font {
      pixelSize: Theme.fontSizeLarge
      family: Theme.fontFamilyHeading
    }
  }

  Component {
    id: pickerComponent
    DatePickerDialog {}
  }
}
