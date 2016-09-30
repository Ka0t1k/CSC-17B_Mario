#-------------------------------------------------
#
# Project created by QtCreator 2015-09-30T22:45:53
#
#-------------------------------------------------

QT       += core gui\
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarioProject
TEMPLATE = app
QMAKE_CXXFLAGS+= -std=c++11 -O3
QMAKE_LFLAGS +=  -std=c++11

RESOURCES += mario.qrc


SOURCES += main.cpp \
    gameboard.cpp \
    brick.cpp \
    safe.cpp \
    mario.cpp \
    person.cpp \
    model.cpp \
    splashscreen.cpp \
    header.cpp \
    background.cpp \
    mushroom.cpp \
    gold.cpp \
    view.cpp \
    paintvisitor.cpp \
    flame.cpp \
    insert.cpp \
    bomb.cpp \
    ground.cpp \
    warppipe.cpp \
    piranhaplant.cpp \
    smash.cpp \
    questnbox.cpp

HEADERS  += gameboard.h \
    brick.h \
    safe.h \
    mario.h \
    person.h \
    model.h \
    splashscreen.h \
    header.h \
    background.h \
    mushroom.h \
    gold.h \
    view.h \
    paintvisitor.h \
    flame.h \
    insert.h \
    bomb.h \
    ground.h \
    warppipe.h \
    piranhaplant.h \
    smash.h \
    questnbox.h

DISTFILES += \
    images/gameover.png
