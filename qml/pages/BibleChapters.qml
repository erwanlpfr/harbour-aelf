/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import harbour.org.aelf 1.0

Page {
    id: chaptersPage

    allowedOrientations: Orientation.All

    property string bookName: ""
    property string bookAbbreviation: ""
    property string bookCode: ""
    property int chapterCount: 0

    ListModel {
        id: chaptersModel
        
        Component.onCompleted: {
            for (var i = 1; i <= chapterCount; i++) {
                append({ chapterNumber: i })
            }
        }
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        PullDownMenu {
            MenuItem {
                text: qsTr("Retour aux livres")
                onClicked: pageStack.pop()
            }
        }

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: bookName
                description: qsTr("%1 chapitres").arg(chapterCount)
            }


            SilicaGridView {
                id: chaptersGrid
                anchors.left: parent.left
                anchors.right: parent.right
                height: contentHeight
                
                cellWidth: width / 4
                cellHeight: Theme.itemSizeMedium
                
                model: chaptersModel
                
                delegate: BackgroundItem {
                    id: chapterItem
                    width: GridView.view.cellWidth
                    height: GridView.view.cellHeight
                    
                    Label {
                        anchors.centerIn: parent
                        text: model.chapterNumber
                        color: chapterItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                        font.pixelSize: Theme.fontSizeLarge
                        font.bold: true
                    }
                    
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("BibleVerses.qml"), {
                            bookName: chaptersPage.bookName,
                            bookAbbreviation: chaptersPage.bookAbbreviation,
                            bookCode: BibleDatabase.getBookCodeFromAbbreviation(chaptersPage.bookAbbreviation),
                            chapterNumber: model.chapterNumber
                        })
                    }
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
