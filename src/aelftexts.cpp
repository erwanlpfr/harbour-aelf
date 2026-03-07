/*
 * SPDX-FileCopyrightText: 2026 erwanlpfr
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "aelftexts.h"
#include <QCoreApplication>

QString AelfTexts::gloriaPatri()
{
    return QCoreApplication::translate("AelfFormatter",
        "Gloire au Père, et au Fils, et au Saint-Esprit, "
        "pour les siècles des siècles. Amen.");
}

QString AelfTexts::notrePereText()
{
    return QCoreApplication::translate("AelfFormatter",
        "Notre Père, qui es aux cieux, <br>"
        "que ton nom soit sanctifié,<br>"
        "que ton règne vienne,<br>"
        "que ta volonté soit faite sur la terre comme au ciel.<br>"
        "Donne-nous aujourd'hui notre pain de ce jour.<br>"
        "Pardonne-nous nos offenses,<br>"
        "comme nous pardonnons aussi à ceux qui nous ont offensés.<br>"
        "Et ne nous laisse pas entrer en tentation<br>"
        "mais délivre-nous du Mal.<br><br>"
        "Amen"
    );
}

QString AelfTexts::oraisonSuffix()
{
    return QCoreApplication::translate("AelfFormatter",
        "Que le Seigneur nous bénisse, qu'il nous garde de tout mal, "
        "et nous conduise à la vie éternelle.<br>Amen."
    );
}

QString AelfTexts::reponsMarker()
{
    return AelfLiturgy::reponsBlock(QCoreApplication::translate("AelfFormatter", "Répons"));
}
