HEADERS = Garma.h \
    define_global.h \
    dialogmanager.h \
    gmessagebox.h \
    gprogressdialog.h \
    inputguard.h
SOURCES = Garma.cpp \
    dialogmanager.cpp \
    gmessagebox.cpp \
    gprogressdialog.cpp \
    main.cpp
QT      += dbus gui widgets
CONFIG += link_pkgconfig
PKGCONFIG += dtkwidget

lessThan(QT_MAJOR_VERSION, 6){
  unix:!macx:QT += x11extras
}
TARGET  = garma

unix:!macx:LIBS    += -lX11
unix:!macx:DEFINES += WS_X11

# override: qmake PREFIX=/some/where/else
isEmpty(PREFIX) {
  PREFIX = /usr
}

# 翻译
TRANSLATIONS += $$PWD/translations/garma_zh_CN.ts
# Automating generation .qm files from .ts files
!system($$PWD/translate_generation.sh): error("Failed to generate translation")
translations.path = /usr/share/garma/translations/
translations.files = translations/*.qm

target.path = $$PREFIX/bin

INSTALLS += target
