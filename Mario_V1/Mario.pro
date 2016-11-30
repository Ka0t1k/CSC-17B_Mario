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


SOURCES += main.cpp\
    myscene.cpp \
    player.cpp \
    coin.cpp \
    backgrounditem.cpp \
    castle.cpp \
    goomba.cpp \
    questbox.cpp \
    turtle.cpp \
    piranha.cpp \
    brickplatform.cpp \
    flag.cpp \
    notebox.cpp \
    coincounter.cpp \
    warptube.cpp \
    conveyor.cpp \
    giantgoomba.cpp \
    stretch.cpp \
    wallplatform.cpp \
    stairblock.cpp \
    bomb.cpp \
    redturtle.cpp \
    spiny.cpp \
    score.cpp \
    timer.cpp

HEADERS  += \
    myscene.h \
    player.h \
    coin.h \
    backgrounditem.h \
    castle.h \
    goomba.h \
    questbox.h \
    turtle.h \
    piranha.h \
    brickplatform.h \
    objecttype.h \
    flag.h \
    notebox.h \
    coincounter.h \
    warptube.h \
    conveyor.h \
    giantgoomba.h \
    stretch.h \
    wallplatform.h \
    stairblock.h \
    bomb.h \
    redturtle.h \
    spiny.h \
    score.h \
    timer.h

FORMS    +=

RESOURCES += \
    mario.qrc
RC_ICONS = mario_folder.ico
