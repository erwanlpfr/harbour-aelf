/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

pragma Singleton
import QtQuick 2.6
import Nemo.Configuration 1.0

QtObject {
    id: bibleSettings

    property ConfigurationGroup settings: ConfigurationGroup {
        path: "/apps/harbour-aelf/bible"

        property string favorites: "[]"
    }

    function _favoriteKey(bookCode, chapter, verse) {
        return bookCode + ":" + chapter + ":" + verse
    }

    function getFavorites() {
        try {
            return JSON.parse(settings.favorites)
        } catch(e) {
            return []
        }
    }

    function _findIndex(favs, key) {
        for (var i = 0; i < favs.length; i++) {
            if (favs[i].key === key) {
                return i
            }
        }
        return -1
    }

    function addFavorite(bookCode, chapter, verse, bookName, bookAbbreviation) {
        var favs = getFavorites()
        var key = _favoriteKey(bookCode, chapter, verse)
        if (_findIndex(favs, key) < 0) {
            favs.push({
                key: key,
                bookCode: bookCode,
                bookName: bookName,
                bookAbbreviation: bookAbbreviation,
                chapter: chapter,
                verse: verse,
                date: new Date().toISOString()
            })
            settings.favorites = JSON.stringify(favs)
        }
    }

    function removeFavorite(bookCode, chapter, verse) {
        var favs = getFavorites()
        var key = _favoriteKey(bookCode, chapter, verse)
        var idx = _findIndex(favs, key)
        if (idx >= 0) {
            favs.splice(idx, 1)
            settings.favorites = JSON.stringify(favs)
        }
    }
}
