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
    backgrounditem.cpp \
    bomb.cpp \
    brickplatform.cpp \
    castle.cpp \
    coin.cpp \
    coincounter.cpp \
    conveyor.cpp \
    flag.cpp \
    giantgoomba.cpp \
    goomba.cpp \
    myscene.cpp \
    notebox.cpp \
    piranha.cpp \
    player.cpp \
    questbox.cpp \
    redturtle.cpp \
    score.cpp \
    spiny.cpp \
    stairblock.cpp \
    stretch.cpp \
    timer.cpp \
    turtle.cpp \
    wallplatform.cpp \
    warptube.cpp

HEADERS  += mainwindow.h \
            settings.h \
            title.h \
            view.h \
    LibHeaders/about_dialog.h \
    LibHeaders/ara_sound_manager.h \
    backgrounditem.h \
    bomb.h \
    brickplatform.h \
    castle.h \
    coin.h \
    coincounter.h \
    conveyor.h \
    flag.h \
    giantgoomba.h \
    goomba.h \
    myscene.h \
    notebox.h \
    objecttype.h \
    piranha.h \
    player.h \
    questbox.h \
    redturtle.h \
    score.h \
    spiny.h \
    stairblock.h \
    stretch.h \
    timer.h \
    turtle.h \
    wallplatform.h \
    warptube.h

FORMS    +=

RESOURCES += \
    mario.qrc

#Libraries Headers Path
INCLUDEPATH += $$PWD/LibHeaders
DEPENDPATH += $$PWD/LibHeaders

#------------------------------------------------------------#
#-----------------------Mac Libraries------------------------#
#------------------------------------------------------------#
macx: LIBS += -L$$PWD/'MacLib/' -lAra_About_Dialog
macx: PRE_TARGETDEPS += $$PWD/'MacLib/libAra_About_Dialog.a'

macx: LIBS += -L$$PWD/'MacLib/' -lAra_Sound_Manager
macx: PRE_TARGETDEPS += $$PWD/'MacLib/libAra_Sound_Manager.a'

#------------------------------------------------------------#
#-----------------------Win Libraries------------------------#
#------------------------------------------------------------#
win32: LIBS += -L$$PWD/'WinLib/' -lAra_About_Dialog
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/'WinLib/Ara_About_Dialog.lib'
else:win32-g++: PRE_TARGETDEPS += $$PWD/'WinLib/libAra_About_Dialog.a'

win32: LIBS += -L$$PWD/'WinLib/' -lAra_Sound_Manager
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/'WinLib/Ara_Sound_Manager.lib'
else:win32-g++: PRE_TARGETDEPS += $$PWD/'WinLib/libAra_Sound_Manager.a'
