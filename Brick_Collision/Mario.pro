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
    glowbrick.cpp \
    turtle.cpp \
    piranha.cpp

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
    piranha.h

FORMS    +=

RESOURCES += \
    mario.qrc
RC_ICONS = mario_folder.ico
