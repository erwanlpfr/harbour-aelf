# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-aelf

CONFIG += sailfishapp
QT += sql concurrent

RESOURCES += resources.qrc

SOURCES += \
  src/aelf.cpp \
  src/aelfapi.cpp \
  src/errorhandler.cpp \
  src/errormanager.cpp \
  src/hourliturgy.cpp \
  src/hourliturgymodel.cpp \
  src/aelfhourliturgyparser.cpp \
  src/information.cpp \
  src/informationmodel.cpp \
  src/liturgicalcolorhelper.cpp \
  src/liturgybasemodel.cpp \
  src/aelfformatter.cpp \
  src/aelftexts.cpp \
  src/liturgyrepository.cpp \
  src/liturgyservice.cpp \
  src/mass.cpp \
  src/massmodel.cpp \
  src/aelfmassparser.cpp \
  src/reading.cpp \
  src/readingtabmodel.cpp \
  src/zone.cpp \
  src/biblebook.cpp \
  src/bibleverse.cpp \
  src/bibledatabase.cpp \
  src/biblebooksmodel.cpp \
  src/bibleversesmodel.cpp

DISTFILES += qml/harbour-aelf.qml \
    qml/AppSettings.qml \
    qml/qmldir \
    qml/components/headers/PageHeaderWithDate.qml \
    qml/components/inputs/DatePicker.qml \
    qml/components/inputs/HourTypePicker.qml \
    qml/components/inputs/MassPicker.qml \
    qml/components/inputs/ZoneCombobox.qml \
    qml/components/Clipboard.qml \
    qml/components/ErrorBanner.qml \
    qml/components/ui/MainPullDownMenu.qml \
    qml/components/layout/Reading.qml \
    qml/cover/CoverPage.qml \
    qml/modules/Opal/Attributions/OpalTabsAttribution.qml \
    qml/modules/Opal/Tabs/Tab.qml \
    qml/modules/Opal/Tabs/TabItem.qml \
    qml/modules/Opal/Tabs/TabView.qml \
    qml/modules/Opal/Tabs/private/ColorInterpolator.qml \
    qml/modules/Opal/Tabs/private/TabBar.qml \
    qml/modules/Opal/Tabs/private/TabButton.qml \
    qml/pages/HourLiturgy.qml \
    qml/pages/Information.qml \
    qml/pages/Mass.qml \
    qml/pages/About.qml \
    qml/pages/Settings.qml \
    qml/pages/Bible.qml \
    qml/pages/BibleChapters.qml \
    qml/pages/BibleVerses.qml \
    qml/js/DateHelper.js \
    qml/js/StringHelper.js \
    qml/js/BibleHelper.js \
    qml/js/ReadingHelper.js \
    rpm/harbour-aelf.changes.in \
    rpm/harbour-aelf.changes.run.in \
    rpm/harbour-aelf.spec \
    translations/*.ts \
    harbour-aelf.desktop \
    .clang-format

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# Install bible database
bible_db.files = assets/bible.db
bible_db.path = /usr/share/$${TARGET}
INSTALLS += bible_db

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# French is the source language, English is the translation
TRANSLATIONS += translations/harbour-aelf-en.ts

HEADERS += \
  src/aelfapi.h \
  src/errorhandler.h \
  src/errormanager.h \
  src/hourliturgy.h \
  src/hourliturgymodel.h \
  src/aelfhourliturgyparser.h \
  src/information.h \
  src/informationmodel.h \
  src/liturgicalcolorhelper.h \
  src/liturgybasemodel.h \
  src/aelfformatter.h \
  src/aelftexts.h \
  src/htmlutils.h \
  src/liturgyidentifierkey.h \
  src/liturgyrepository.h \
  src/liturgyservice.h \
  src/mass.h \
  src/massmodel.h \
  src/aelfmassparser.h \
  src/reading.h \
  src/readingtabmodel.h \
  src/zone.h \
  src/biblebook.h \
  src/bibleverse.h \
  src/bibledatabase.h \
  src/biblebooksmodel.h \
  src/bibleversesmodel.h

 include(libs/opal.pri)
