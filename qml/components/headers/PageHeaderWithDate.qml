/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import "../inputs" as Inputs

PageHeader {
  id: header
  
  property alias datePicker: datePicker
  
  Inputs.DatePicker {
    id: datePicker
    width: header.width / 2
    onDateChanged: header.dateChanged(date)
  }
  
  signal dateChanged(date date)
}
