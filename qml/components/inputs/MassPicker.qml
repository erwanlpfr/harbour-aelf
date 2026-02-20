/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.2
import Sailfish.Silica 1.0
import "../../js/StringHelper.js" as StringHelper

Page {
  id: page

  property var massNames: []
  property int selectedIndex: 0

  signal massSelected(int index)

  SilicaFlickable {
    anchors.fill: parent
    contentHeight: column.height

    VerticalScrollDecorator {}

    Column {
      id: column
      width: parent.width

      PageHeader {
        title: qsTr("Messe")
      }

      Repeater {
        model: massNames

        TextSwitch {
          text: StringHelper.toTitleCase(modelData)
          checked: index === page.selectedIndex
          automaticCheck: false
          onClicked: {
            page.selectedIndex = index
            page.massSelected(index)
            pageStack.navigateBack()
          }
        }
      }
    }
  }
}
