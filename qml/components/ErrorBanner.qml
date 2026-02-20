

/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
import QtQuick 2.6
import Sailfish.Silica 1.0

Item {
  id: errorBanner

  property alias text: errorLabel.text
  property bool showBanner: false
  property bool showRetry: false

  signal retryClicked
  signal dismissed

  height: showBanner ? errorRow.height + Theme.paddingLarge : 0
  visible: showBanner
  Behavior on height {
    NumberAnimation {
      duration: 200
      easing.type: Easing.InOutQuad
    }
  }

  Rectangle {
    anchors.fill: parent
    color: Theme.rgba(Theme.highlightBackgroundColor, 0.2)
    radius: Theme.paddingSmall
  }

  Row {
    id: errorRow
    anchors {
      left: parent.left
      right: parent.right
      top: parent.top
      margins: Theme.paddingMedium
    }
    spacing: Theme.paddingMedium

    Image {
      id: errorIcon
      anchors.top: parent.top
      source: "image://theme/icon-m-warning"
      width: Theme.iconSizeSmall
      height: Theme.iconSizeSmall
    }

    Column {
      width: parent.width - errorIcon.width - dismissButton.width - 2 * Theme.paddingMedium
      spacing: Theme.paddingSmall

      Text {
        id: errorLabel
        width: parent.width
        color: Theme.highlightColor
        font.pixelSize: Theme.fontSizeSmall
        wrapMode: Text.WordWrap
      }

      Button {
        visible: showRetry
        text: qsTr("Réessayer")
        preferredWidth: Theme.buttonWidthSmall
        onClicked: retryClicked()
      }
    }

    IconButton {
      id: dismissButton
      anchors.top: parent.top
      icon.source: "image://theme/icon-m-dismiss"
      onClicked: dismissed()
    }
  }
}
