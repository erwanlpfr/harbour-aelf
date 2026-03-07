/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import harbour.org.aelf 1.0

Page {
    id: biblePage

    allowedOrientations: Orientation.All

    BibleBooksModel {
        id: ancientTestamentModel
        section: qsTr("Ancien Testament")
        Component.onCompleted: loadBooks()
    }

    BibleBooksModel {
        id: poeticBooksModel
        section: qsTr("Livres Poétiques")
        Component.onCompleted: loadBooks()
    }

    BibleBooksModel {
        id: prophetsModel
        section: qsTr("Prophètes")
        Component.onCompleted: loadBooks()
    }

    BibleBooksModel {
        id: newTestamentModel
        section: qsTr("Nouveau Testament")
        Component.onCompleted: loadBooks()
    }

    Component {
        id: bookGridItem
        
        BackgroundItem {
            id: bookItem
            width: GridView.view ? GridView.view.cellWidth : 100
            height: GridView.view ? GridView.view.cellHeight : 100
            
            property string bookName: model.name
            property string bookAbbr: model.abbreviation
            property int bookChapters: model.chapters
            
            Column {
                anchors.centerIn: parent
                width: parent.width - Theme.paddingMedium
                spacing: Theme.paddingSmall
                
                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: bookItem.bookAbbr
                    color: bookItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    font.pixelSize: Theme.fontSizeLarge
                    font.bold: true
                }
                
                Label {
                    width: parent.width
                    text: bookItem.bookName
                    color: bookItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    font.pixelSize: Theme.fontSizeExtraSmall
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                    maximumLineCount: 2
                    truncationMode: TruncationMode.Fade
                }
                
                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: bookItem.bookChapters + " " + qsTr("chap.")
                    color: bookItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                    font.pixelSize: Theme.fontSizeTiny
                }
            }
            
            onClicked: {
                pageStack.push(Qt.resolvedUrl("BibleChapters.qml"), {
                    bookName: bookItem.bookName,
                    bookAbbreviation: bookItem.bookAbbr,
                    chapterCount: bookItem.bookChapters
                })
            }
        }
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        PullDownMenu {
            MenuItem {
                text: qsTr("Rechercher")
                onClicked: console.log("Search functionality not implemented yet")
            }
            MenuItem {
                text: qsTr("Favoris")
                onClicked: pageStack.push(Qt.resolvedUrl("BibleFavorites.qml"))
            }
        }

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("Bible")
                description: qsTr("Ancien et Nouveau Testament")
            }

            SectionHeader {
                text: qsTr("Ancien Testament")
            }

            SilicaGridView {
                id: ancientTestamentGrid
                anchors.left: parent.left
                anchors.right: parent.right
                height: contentHeight
                
                cellWidth: width / 3
                cellHeight: Theme.itemSizeExtraLarge
                
                model: ancientTestamentModel
                delegate: bookGridItem
            }

            SectionHeader {
                text: qsTr("Livres Poétiques")
            }

            SilicaGridView {
                id: poeticBooksGrid
                anchors.left: parent.left
                anchors.right: parent.right
                height: contentHeight
                
                cellWidth: width / 3
                cellHeight: Theme.itemSizeExtraLarge
                
                model: poeticBooksModel
                delegate: bookGridItem
            }

            SectionHeader {
                text: qsTr("Prophètes")
            }

            SilicaGridView {
                id: prophetsGrid
                anchors.left: parent.left
                anchors.right: parent.right
                height: contentHeight
                
                cellWidth: width / 3
                cellHeight: Theme.itemSizeExtraLarge
                
                model: prophetsModel
                delegate: bookGridItem
            }

            SectionHeader {
                text: qsTr("Nouveau Testament")
            }

            SilicaGridView {
                id: newTestamentGrid
                anchors.left: parent.left
                anchors.right: parent.right
                height: contentHeight
                
                cellWidth: width / 3
                cellHeight: Theme.itemSizeExtraLarge
                
                model: newTestamentModel
                delegate: bookGridItem
            }
            
            Item {
                width: parent.width
                height: Theme.paddingLarge
            }
        }

        VerticalScrollDecorator { }
    }
}
