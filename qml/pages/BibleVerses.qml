/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import Sailfish.Share 1.0
import harbour.org.aelf 1.0
import "../components"
import "../js/BibleHelper.js" as BibleHelper
import ".." as Root

Page {
    id: versesPage

    allowedOrientations: Orientation.All

    property string bookName: ""
    property string bookAbbreviation: ""
    property string bookCode: ""
    property int chapterNumber: 0
    property int scrollToVerse: -1
    
    Clipboard {
        id: clipboard
    }
    
    function copyVerse(verseNum, verseText) {
        var text = BibleHelper.formatVerseText(bookName, chapterNumber, verseNum, verseText)
        clipboard.setText(text)
    }
    
    function shareVerse(verseNum, verseText) {
        var text = BibleHelper.formatVerseText(bookName, chapterNumber, verseNum, verseText)
        shareAction.resources = [text]
        shareAction.trigger()
    }
    
    ShareAction {
        id: shareAction
        mimeType: "text/plain"
    }

    AppNotification {
        id: favoriteNotification
    }

    BibleVersesModel {
        id: versesModel
        bookCode: versesPage.bookCode
        chapter: versesPage.chapterNumber
        
        Component.onCompleted: {
            if (bookCode && chapter > 0) {
                loadVerses()
            }
        }
    }
    
    onBookCodeChanged: {
        if (bookCode && chapterNumber > 0) {
            versesModel.loadVerses()
        }
    }
    
    onChapterNumberChanged: {
        if (bookCode && chapterNumber > 0) {
            versesModel.loadVerses()
        }
    }

    Timer {
        id: scrollTimer
        interval: 100
        onTriggered: {
            if (scrollToVerse > 0 && scrollToVerse <= versesModel.count) {
                versesList.currentIndex = scrollToVerse - 1
                var item = versesList.currentItem
                if (item) {
                    var mapped = item.mapToItem(flickable.contentItem, 0, 0)
                    var maxY = flickable.contentHeight - flickable.height
                    flickable.contentY = Math.max(0, Math.min(mapped.y - Theme.paddingLarge, maxY))
                }
                item.flash()
                scrollToVerse = -1
            }
        }
    }

    Connections {
        target: versesModel
        onCountChanged: {
            if (scrollToVerse > 0) {
                scrollTimer.restart()
            }
        }
    }

    SilicaFlickable {
        id: flickable
        anchors.fill: parent
        contentHeight: column.height

        PullDownMenu {
            MenuItem {
                text: qsTr("Retour aux chapitres")
                onClicked: pageStack.pop()
            }
        }

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingLarge

            ErrorBanner {
                id: errorBanner
                anchors {
                    left: parent.left
                    right: parent.right
                }
                text: ErrorManager.error
                showBanner: ErrorManager.hasError
                showRetry: ErrorManager.showRetry

                onRetryClicked: {
                    ErrorManager.retry()
                    versesModel.loadVerses()
                }
                onDismissed: ErrorManager.clearError()
            }

            PageHeader {
                title: bookName + " " + chapterNumber
                description: versesModel.count > 0 ? qsTr("%1 versets").arg(versesModel.count) : ""
            }

            SilicaListView {
                id: versesList
                anchors.left: parent.left
                anchors.right: parent.right
                height: contentHeight

                model: versesModel

                delegate: ListItem {
                    id: verseItem
                    contentHeight: verseContent.height

                    function flash()
                    {
                        flashAnimation.start()
                    }

                    Rectangle {
                        id: flashOverlay
                        anchors.fill: parent
                        color: Theme.highlightBackgroundColor
                        opacity: 0

                        SequentialAnimation {
                            id: flashAnimation
                            NumberAnimation { target: flashOverlay; property: "opacity"; to: 0.5; duration: 200 }
                            PauseAnimation { duration: 300 }
                            NumberAnimation { target: flashOverlay; property: "opacity"; to: 0; duration: 400 }
                        }
                    }

                    menu: ContextMenu {
                        MenuItem {
                            text: qsTr("Copier")
                            onClicked: copyVerse(model.verseNumber, model.verseText)
                        }
                        MenuItem {
                            text: qsTr("Partager")
                            onClicked: shareVerse(model.verseNumber, model.verseText)
                        }
                        MenuItem {
                            text: qsTr("Ajouter aux favoris")
                            onClicked: {
                                Root.BibleSettings.addFavorite(versesPage.bookCode, versesPage.chapterNumber, model.verseNumber, versesPage.bookName, versesPage.bookAbbreviation)
                                var ref = BibleHelper.formatVerseReference(versesPage.bookName, versesPage.chapterNumber, model.verseNumber)
                                favoriteNotification.previewSummary = qsTr("Ajouté aux favoris")
                                favoriteNotification.previewBody = ref
                                favoriteNotification.publish()
                            }
                        }
                    }

                    Row {
                        id: verseContent
                        width: parent.width
                        spacing: Theme.paddingSmall
                        anchors.left: parent.left
                        anchors.leftMargin: Theme.horizontalPageMargin
                        anchors.right: parent.right
                        anchors.rightMargin: Theme.horizontalPageMargin

                        Label {
                            id: verseNumberLabel
                            text: model.verseNumber
                            color: Theme.secondaryHighlightColor
                            font.pixelSize: Root.AppSettings.scaledFont(Theme.fontSizeExtraSmall)
                            font.bold: true
                            width: implicitWidth
                            anchors.top: parent.top
                            anchors.topMargin: Theme.paddingSmall
                        }

                        Label {
                            width: parent.width - verseNumberLabel.width - Theme.paddingSmall
                            text: model.verseText
                            wrapMode: Text.WordWrap
                            color: verseItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                            font.pixelSize: Root.AppSettings.scaledFont(Theme.fontSizeMedium)
                        }
                    }

                    onClicked: copyVerse(model.verseNumber, model.verseText)
                }

                ViewPlaceholder {
                    enabled: versesModel.count === 0
                    text: qsTr("Aucun verset disponible")
                    hintText: qsTr("Tirez vers le bas pour actualiser")
                }
            }

            Item {
                width: parent.width
                height: Theme.paddingLarge
            }
        }

        VerticalScrollDecorator { }
    }
}
