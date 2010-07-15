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
    info.cpp \
    librarydialog.cpp \
    devtools.cpp \
    infodialog.cpp \
    translucentbutton.cpp \
    settingswindow.cpp \
    settings.cpp \
    bookmarksdialog.cpp

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
    info.h \
    librarydialog.h \
    devtools.h \
    infodialog.h \
    translucentbutton.h \
    settingswindow.h \
    settings.h \
    bookmarksdialog.h \
    opserrorhandler.h \
    containerhandler.h

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
    styles/day.js

DEFINES += \
    USE_FILE32API

unix: LIBS += -lz
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
    desktop.files += dorian.desktop

    icon48.path = $$DATADIR/icons/hicolor/48x48
    icon48.files += pkg/maemo/icon-48/dorian.png

    icon64.path = $$DATADIR/icons/hicolor/64x64/apps
    icon64.files += pkg/maemo/icon-scalable/dorian.png
}
