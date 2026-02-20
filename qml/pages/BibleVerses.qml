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

Page {
    id: versesPage

    allowedOrientations: Orientation.All

    property string bookName: ""
    property string bookAbbreviation: ""
    property string bookCode: ""
    property int chapterNumber: 0
    
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

    SilicaFlickable {
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
                    
                    menu: ContextMenu {
                        MenuItem {
                            text: qsTr("Copier")
                            onClicked: copyVerse(model.verseNumber, model.verseText)
                        }
                        MenuItem {
                            text: qsTr("Partager")
                            onClicked: shareVerse(model.verseNumber, model.verseText)
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
                            font.pixelSize: Theme.fontSizeExtraSmall
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
                            font.pixelSize: Theme.fontSizeMedium
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
