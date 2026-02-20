/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import "../../js/DateHelper.js" as DateHelper

Item {
  id: dateDatePicker

  property date date: new Date()

  height: Theme.itemSizeLarge

  Label {
    id: dateLabel
    text: DateHelper.formatRelativeDate(dateDatePicker.date)
    color: Theme.secondaryColor
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

  MouseArea {
    id: mouseArea
    anchors.fill: parent
    onClicked: {
      var dialog = pageStack.push(pickerComponent, {
                                    "date": dateDatePicker.date
                                  })

      dialog.accepted.connect(function () {
        dateDatePicker.date = dialog.date
      })
    }

    onPressedChanged: {
      if (pressed) {
        dateLabel.opacity = 0.6
      } else {
        dateLabel.opacity = 1.0
      }
    }
  }

  Component {
    id: pickerComponent
    DatePickerDialog {}
  }
}
