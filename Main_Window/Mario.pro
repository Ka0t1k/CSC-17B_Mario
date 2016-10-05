#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T19:50:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mario
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myscene.cpp \
    player.cpp \
    coin.cpp \
    backgrounditem.cpp

HEADERS  += mainwindow.h \
    myscene.h \
    player.h \
    coin.h \
    backgrounditem.h

FORMS    += mainwindow.ui

RESOURCES += \
    mario.qrc
RC_ICONS = marioi.ico
