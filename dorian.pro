QT += webkit xml

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    bookview.cpp \
    unzip/unzip.c \
    unzip/ioapi.c \
    extractzip.cpp \
    library.cpp \
    book.cpp \
    librarydialog.cpp \
    devtools.cpp \
    infodialog.cpp \
    translucentbutton.cpp \
    settingswindow.cpp \
    settings.cpp \
    bookmarksdialog.cpp \
    sortedlibrary.cpp \
    bookmarkinfodialog.cpp \
    dialog.cpp \
    chaptersdialog.cpp \
    fullscreenwindow.cpp \
    trace.cpp

HEADERS += \
    mainwindow.h \
    bookview.h \
    selectionsuppressor.h \
    opshandler.h \
    unzip/unzip.h \
    unzip/ioapi.h \
    extractzip.h \
    library.h \
    book.h \
    librarydialog.h \
    devtools.h \
    infodialog.h \
    translucentbutton.h \
    settingswindow.h \
    settings.h \
    bookmarksdialog.h \
    xmlerrorhandler.h \
    containerhandler.h \
    sortedlibrary.h \
    ncxhandler.h \
    bookmarkinfodialog.h \
    dialog.h \
    chaptersdialog.h \
    fullscreenwindow.h \
    trace.h

RESOURCES += \
    dorian.qrc

OTHER_FILES += \
    TODO.txt \
    pkg/acknowledgements.txt \
    pkg/maemo/postinst \
    pkg/maemo/dorian.desktop \
    pkg/maemo/control \
    pkg/maemo/changelog \
    pkg/maemo/build.sh \
    styles/night.css \
    pkg/changelog \
    pkg/maemo/build-scratchbox.sh \
    styles/sand.css \
    styles/default.css \
    pkg/version.txt \
    styles/sand.js \
    styles/night.js \
    styles/default.js \
    styles/day.js \
    www/index.html

DEFINES += \
    USE_FILE32API \
    DORIAN_TEST_MODEL

include(modeltest/modeltest.pri)

unix {
    LIBS += -lz
}
windows {
    # FIXME: Build zlib, too
}
maemo5 {
    QT += maemo5
    isEmpty(PREFIX) {
        PREFIX = /usr
    }
    BINDIR = $$PREFIX/bin
    DATADIR =$$PREFIX/share
    DEFINES += DATADIR=\\\"$$DATADIR\\\" PKGDATADIR=\\\"$$PKGDATADIR\\\"

    # For "make install"

    INSTALLS += target desktop icon48 iconscalable

    target.path = $$BINDIR

    desktop.path = $$DATADIR/applications/hildon
    desktop.files += pkg/maemo/dorian.desktop

    icon48.path = $$DATADIR/icons/hicolor/48x48/hildon
    icon48.files += pkg/maemo/icon-48/dorian.png

    iconscalable.path = $$DATADIR/icons/hicolor/scalable/hildon
    iconscalable.files += pkg/maemo/icon-scalable/dorian.png
}
