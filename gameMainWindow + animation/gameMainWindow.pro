#-------------------------------------------------
#
# Project created by QtCreator 2016-09-28T17:51:53
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gameMainWindow
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
           mainwindow.cpp \
           settings.cpp \
           title.cpp \
           view.cpp \
    placeholderscene.cpp \
    backgrounditem.cpp \
    castle.cpp \
    coin.cpp \
    glowbrick.cpp \
    goomba.cpp \
    myscene.cpp \
    piranha.cpp \
    player.cpp \
    questbox.cpp \
    turtle.cpp \
    about_dialog.cpp \
    ara_sound_manager.cpp

HEADERS  += mainwindow.h \
            settings.h \
            title.h \
            view.h \
    placeholderscene.h \
    backgrounditem.h \
    castle.h \
    coin.h \
    glowbrick.h \
    goomba.h \
    myscene.h \
    piranha.h \
    player.h \
    questbox.h \
    turtle.h \
    about_dialog.h \
    ara_sound_manager.h

FORMS    += \
    about_dialog.ui \
    ara_sound_manager.ui

RESOURCES += \
    mario.qrc \
    images/AD_mario.qrc \
    music/ara_sound_rsc.qrc
