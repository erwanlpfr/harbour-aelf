/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import "../js/DateHelper.js" as DateHelper
import ".." as Root

ListItem {
    id: favoriteCard

    property var favorite
    property int favoriteIndex: -1

    signal removed(int index)

    contentHeight: favoriteColumn.height + Theme.paddingMedium * 2

    menu: ContextMenu {
        MenuItem {
            text: qsTr("Retirer des favoris")
            onClicked: favoriteCard.remorseAction(qsTr("Suppression"), function() {
                Root.BibleSettings.removeFavorite(favorite.bookCode, favorite.chapter, favorite.verse)
                favoriteCard.removed(favoriteIndex)
            })
        }
    }

    Column {
        id: favoriteColumn
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        spacing: Theme.paddingSmall

        Label {
            width: parent.width
            text: favorite.bookName + " " + favorite.chapter + ":" + favorite.verse
            color: favoriteCard.highlighted ? Theme.highlightColor : Theme.primaryColor
            font.pixelSize: Theme.fontSizeMedium
            truncationMode: TruncationMode.Fade
        }

        Label {
            width: parent.width
            text: favorite.date ? DateHelper.formatDateTime(favorite.date) : ""
            visible: favorite.date !== undefined
            color: favoriteCard.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
            font.pixelSize: Theme.fontSizeExtraSmall
        }
    }

    onClicked: {
        pageStack.push(Qt.resolvedUrl("../pages/BibleVerses.qml"), {
            bookName: favorite.bookName,
            bookAbbreviation: favorite.bookAbbreviation,
            bookCode: favorite.bookCode,
            chapterNumber: favorite.chapter,
            scrollToVerse: favorite.verse
        })
    }
}
