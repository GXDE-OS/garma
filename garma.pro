HEADERS = Garma.h \
    gmessagebox.h \
    inputguard.h
SOURCES = Garma.cpp \
    gmessagebox.cpp \
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

target.path = $$PREFIX/bin

INSTALLS += target
