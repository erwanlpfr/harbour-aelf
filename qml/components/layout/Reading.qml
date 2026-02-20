/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import harbour.org.aelf 1.0
import "../../modules/Opal/Tabs" as Tabs
import "../../js/ReadingHelper.js" as ReadingHelper

Tabs.TabItem {
  id: root
  property Reading reading: model.reading

  anchors.fill: parent
  flickable: flickable

  SilicaFlickable {
    id: flickable

    width: parent.width
    height: parent.height
    contentHeight: contentColumn.implicitHeight + Theme.paddingLarge * 2

    VerticalScrollDecorator {}

    Column {
      id: contentColumn
      width: flickable.width - Theme.paddingLarge * 2
      spacing: Theme.paddingLarge
      anchors {
        left: parent.left
        right: parent.right
        margins: Theme.paddingLarge
      }

      Label {
        visible: reading && reading.title
        text: reading.title
        width: parent.width
        wrapMode: Text.WordWrap
        font {
          pixelSize: Theme.fontSizeLarge
          bold: true
        }
      }

      Label {
        visible: reading && reading.gospelVerse
        text: ReadingHelper.applyThemeColors(reading.gospelVerse,
                                             Theme.highlightColor)
        width: parent.width
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        font {
          pixelSize: Theme.fontSizeMedium
          italic: true
        }
      }

      Label {
        visible: (ReadingHelper.isPsalm(reading) || ReadingHelper.isCanticle(
                    reading)) && reading && reading.refrainPsalm
        text: ReadingHelper.applyThemeColors(
                reading.refrainPsalm + (reading.refrainReference
                                        && reading.refrainReference.trim(
                                          ) !== "" ? "\n- " + reading.refrainReference : ""),
                Theme.highlightColor)
        width: parent.width
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
        font {
          pixelSize: Theme.fontSizeMedium
          italic: true
        }
      }

      Label {
        visible: reading && reading.reference
        text: reading.reference
        width: parent.width
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignRight
        font {
          pixelSize: Theme.fontSizeSmall
          italic: true
        }
      }

      Label {
        visible: reading && reading.introRead
        text: reading.introRead
        width: parent.width
        wrapMode: Text.WordWrap
        font.italic: true
      }

      Label {
        visible: reading && reading.content
        text: ReadingHelper.applyThemeColors(reading.content,
                                             Theme.highlightColor)
        width: parent.width
        wrapMode: Text.WordWrap
        textFormat: Text.RichText
      }

      Item {
        width: 1
        height: Theme.itemSizeExtraLarge
      }
    }
  }
}
