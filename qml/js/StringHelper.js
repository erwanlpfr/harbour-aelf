/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

.pragma library

function capitalizeFirstLetter(val) {
  return String(val).charAt(0).toUpperCase() + String(val).slice(1)
}

/**
 * Converts a string to title case (first letter uppercase, rest lowercase)
 * @param {string} val - The string to convert
 * @returns {string} The title-cased string
 */
function toTitleCase(val) {
  var str = String(val).toLowerCase()
  return str.charAt(0).toUpperCase() + str.slice(1)
}
