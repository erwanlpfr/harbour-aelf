/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

.pragma library
.import harbour.org.aelf 1.0 as Aelf

/**
 * Checks if the reading is a Psalm type
 * @param {object} reading - The reading object
 * @returns {boolean} True if reading is a Psalm type
 */
function isPsalm(reading) {
  if (!reading) return false
  var t = reading.readingType
  return t === Aelf.Reading.Psaume ||
         t === Aelf.Reading.PsaumeInvitatoire ||
         t === Aelf.Reading.Psalm
}

/**
 * Checks if the reading is a Canticle type
 * @param {object} reading - The reading object
 * @returns {boolean} True if reading is a Canticle type
 */
function isCanticle(reading) {
  if (!reading) return false
  var t = reading.readingType
  return t === Aelf.Reading.Cantique ||
         t === Aelf.Reading.Canticle ||
         t === Aelf.Reading.CantiqueMariale
}

/**
 * Checks if the reading is an Introduction type
 * @param {object} reading - The reading object
 * @returns {boolean} True if reading is an Introduction
 */
function isIntroduction(reading) {
  if (!reading) return false
  return reading.readingType === Aelf.Reading.Introduction
}


/**
 * Checks if the reading is a Hymn type
 * @param {object} reading - The reading object
 * @returns {boolean} True if reading is a Hymn
 */
function isHymne(reading) {
  if (!reading) return false
  return reading.readingType === Aelf.Reading.Hymne
}

/**
 * Replaces color placeholders in HTML with theme colors
 * @param {string} html - The HTML content with placeholders
 * @param {string} highlightColor - The theme highlight color
 * @returns {string} HTML with replaced colors
 */
function applyThemeColors(html, highlightColor) {
  if (!html) return ""
  return html
    .replace(/\{\{ACCENT_COLOR\}\}/g, highlightColor)
    .replace(/\{\{HIGHLIGHT_COLOR\}\}/g, highlightColor)
}
