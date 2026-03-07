/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

import QtQuick 2.6
import Sailfish.Silica 1.0
import "../components"
import ".." as Root

Page {
    id: favoritesPage

    allowedOrientations: Orientation.All

    property bool loading: true

    ListModel {
        id: favoritesModel
    }

    Component.onCompleted: {
        var favs = Root.BibleSettings.getFavorites()
        for (var i = 0; i < favs.length; i++) {
            favoritesModel.append(favs[i])
        }
        loading = false
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: parent.width

            PageHeader {
                title: qsTr("Favoris")
            }

            BusyIndicator {
                anchors.horizontalCenter: parent.horizontalCenter
                size: BusyIndicatorSize.Large
                running: favoritesPage.loading
                visible: running
            }

            SilicaListView {
                id: favoritesList
                anchors.left: parent.left
                anchors.right: parent.right
                height: contentHeight
                visible: !favoritesPage.loading

                model: favoritesModel

                delegate: FavoriteCard {
                    favorite: model
                    favoriteIndex: index
                    onRemoved: favoritesModel.remove(index)
                }
            }
        }

        ViewPlaceholder {
            enabled: !favoritesPage.loading && favoritesModel.count === 0
            text: qsTr("Aucun favori")
            hintText: qsTr("Maintenez un verset pour l'ajouter aux favoris")
        }

        VerticalScrollDecorator { }
    }
}
