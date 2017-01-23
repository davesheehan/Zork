#-------------------------------------------------
#
# Project created by QtCreator 2015-10-03T21:13:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Designer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    room.cpp \
    player.cpp \
    item.cpp \
    weapon.cpp \
    apparel.cpp \
    nonplayercharacter.cpp

HEADERS  += mainwindow.h \
    room.h \
    player.h \
    item.h \
    weapon.h \
    apparel.h \
    nonplayercharacter.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../../Downloads/West Wing Map.png \
    Resources/West Wing Map.png

RESOURCES += \
    Resources/level1map.qrc
