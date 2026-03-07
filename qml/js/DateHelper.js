/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

.pragma library

/**
 * Formats a date as a relative string ("Aujourd'hui", "Demain", "Hier")
 * or as a localized short date (e.g., "Déc. 9, 2025").
 *
 * @param {Date|string|number} date - The date to format. Can be a Date object, ISO string, or timestamp.
 * @returns {string} The formatted date string.
 */
function formatRelativeDate(date) {
  var checkDate = new Date(date)
  if (isNaN(checkDate.getTime())) {
    console.error("Invalid date provided to formatRelativeDate")
    return qsTr("Date invalide")
  }

  var today = new Date()
  today.setHours(0, 0, 0, 0)

  var tomorrow = new Date(today)
  tomorrow.setDate(tomorrow.getDate() + 1)

  var yesterday = new Date(today)
  yesterday.setDate(yesterday.getDate() - 1)

  checkDate.setHours(0, 0, 0, 0)

  if (checkDate.getTime() === today.getTime()) {
    return qsTr("Aujourd'hui")
  } else if (checkDate.getTime() === tomorrow.getTime()) {
    return qsTr("Demain")
  } else if (checkDate.getTime() === yesterday.getTime()) {
    return qsTr("Hier")
  } else {
    var locale = Qt.locale().name
    return checkDate.toLocaleDateString(locale, {
                                          "month": 'short',
                                          "day": 'numeric',
                                          "year": 'numeric'
                                        })
  }
}

/**
 * Returns the appropriate liturgical hour type based on the current time.
 * Times follow traditional monastic schedule:
 * - Lectures: 3-6 AM (Office of Readings)
 * - Lauds: 6-9 AM (Morning Prayer)
 * - Terce: 9-12 AM (Mid-Morning)
 * - Sext: 12-3 PM (Midday)
 * - None: 3-6 PM (Mid-Afternoon)
 * - Vespers: 6-9 PM (Evening Prayer)
 * - Compline: 9 PM - 3 AM (Night Prayer)
 *
 * @param {object} HourLiturgy - The HourLiturgy enum object from C++
 * @returns {int} The HourLiturgy type enum value
 */
function getHourTypeForTime(HourLiturgy) {
  var hour = new Date().getHours()
  if (hour >= 3 && hour < 6) return HourLiturgy.Lectures
  if (hour >= 6 && hour < 9) return HourLiturgy.Lauds
  if (hour >= 9 && hour < 12) return HourLiturgy.Terce
  if (hour >= 12 && hour < 15) return HourLiturgy.Sext
  if (hour >= 15 && hour < 18) return HourLiturgy.None
  if (hour >= 18 && hour < 21) return HourLiturgy.Vespers
  return HourLiturgy.Compline
}

/**
 * Returns the human-readable name of the current liturgical hour.
 * @returns {string} The localized name of the current hour
 */
function getCurrentHourName() {
  var hour = new Date().getHours()
  if (hour >= 3 && hour < 6) return qsTr("Lectures")
  if (hour >= 6 && hour < 9) return qsTr("Laudes")
  if (hour >= 9 && hour < 12) return qsTr("Tierce")
  if (hour >= 12 && hour < 15) return qsTr("Sexte")
  if (hour >= 15 && hour < 18) return qsTr("None")
  if (hour >= 18 && hour < 21) return qsTr("Vêpres")
  return qsTr("Complies")
}

function formatDate(isoDate) {
  var d = new Date(isoDate)
  return d.toLocaleDateString(Qt.locale(), "d MMM yyyy")
}

function formatDateTime(isoDate) {
  var d = new Date(isoDate)
  return d.toLocaleDateString(Qt.locale(), "d MMM yyyy") + " " + d.toLocaleTimeString(Qt.locale(), "HH:mm")
}
