#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T19:50:28
#
#-------------------------------------------------

QT       += core gui\
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mario
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    myscene.cpp \
    player.cpp \
    coin.cpp \
    backgrounditem.cpp \
    castle.cpp \
    goomba.cpp \
    questbox.cpp \
    glowbrick.cpp \
    turtle.cpp \
    piranha.cpp \
    coincounter.cpp \
    warptube.cpp \
    flag.cpp \
    ara_sound_manager.cpp

HEADERS  += \
    myscene.h \
    player.h \
    coin.h \
    backgrounditem.h \
    castle.h \
    goomba.h \
    questbox.h \
    glowbrick.h \
    turtle.h \
    piranha.h \
    coincounter.h \
    warptube.h \
    flag.h \
    ara_sound_manager.h

FORMS    += \
    ara_sound_manager.ui

RESOURCES += \
    mario.qrc \
    audio/ara_sound_rsc.qrc
RC_ICONS = mario_folder.ico
