/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "aelfapi.h"
#include "biblebooksmodel.h"
#include "bibledatabase.h"
#include "bibleversesmodel.h"
#include "errorhandler.h"
#include "errormanager.h"
#include "hourliturgy.h"
#include "hourliturgymodel.h"
#include "information.h"
#include "informationmodel.h"
#include "liturgyrepository.h"
#include "mass.h"
#include "massmodel.h"
#include "reading.h"
#include "readingtabmodel.h"
#include "zone.h"
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <QScopedPointer>
#include <QtQuick>
#include <sailfishapp.h>

int main(int argc, char* argv[]) {
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> v(SailfishApp::createView());

    LiturgyRepository::instance(app->parent());

    qmlRegisterType<MassModel>("harbour.org.aelf", 1, 0, "MassModel");
    qmlRegisterType<Mass>("harbour.org.aelf", 1, 0, "Mass");
    qmlRegisterType<HourLiturgy>("harbour.org.aelf", 1, 0, "HourLiturgy");
    qmlRegisterType<InformationModel>("harbour.org.aelf", 1, 0, "InformationModel");
    qmlRegisterType<HourLiturgyModel>("harbour.org.aelf", 1, 0, "HourLiturgyModel");
    qmlRegisterType<Reading>("harbour.org.aelf", 1, 0, "Reading");
    qmlRegisterType<ReadingTabModel>("harbour.org.aelf", 1, 0, "ReadingTabModel");
    qmlRegisterType<Zone>("harbour.org.aelf", 1, 0, "Zone");
    qmlRegisterType<BibleBooksModel>("harbour.org.aelf", 1, 0, "BibleBooksModel");
    qmlRegisterType<BibleVersesModel>("harbour.org.aelf", 1, 0, "BibleVersesModel");

    qmlRegisterSingletonType<BibleDatabase>(
        "harbour.org.aelf", 1, 0, "BibleDatabase",
        [](QQmlEngine*, QJSEngine*) -> QObject* { return BibleDatabase::instance(); });

    qmlRegisterSingletonType<ErrorManager>(
        "harbour.org.aelf", 1, 0, "ErrorManager",
        [](QQmlEngine*, QJSEngine*) -> QObject* { return new ErrorManager(); });

    v->setSource(SailfishApp::pathTo("qml/harbour-aelf.qml"));
    v->show();

    return app->exec();
}
