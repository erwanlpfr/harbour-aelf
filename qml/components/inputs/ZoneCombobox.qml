/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0

ComboBox {
  id: zoneCombobox
  label: qsTr("Changer la région")

  property string value: "france"
  
  onValueChanged: {
    for (var i = 0; i < zoneModel.count; i++) {
      if (zoneModel.get(i).key === value) {
        currentIndex = i
        break
      }
    }
  }
  
  onCurrentIndexChanged: {
    if (currentIndex >= 0 && currentIndex < zoneModel.count) {
      value = zoneModel.get(currentIndex).key
    }
  }

  ListModel {
    id: zoneModel
    ListElement {
      key: "france"
      display: qsTr("France")
    }
    ListElement {
      key: "afrique"
      display: qsTr("Afrique")
    }
    ListElement {
      key: "suisse"
      display: qsTr("Suisse")
    }
    ListElement {
      key: "canada"
      display: qsTr("Canada")
    }
    ListElement {
      key: "belgique"
      display: qsTr("Belgique")
    }
    ListElement {
      key: "luxembourg"
      display: qsTr("Luxembourg")
    }
    ListElement {
      key: "romain"
      display: qsTr("Romain")
    }
  }

  menu: ContextMenu {
    Repeater {
      model: zoneModel
      MenuItem {
        text: qsTr(model.display)
      }
    }
  }
}
