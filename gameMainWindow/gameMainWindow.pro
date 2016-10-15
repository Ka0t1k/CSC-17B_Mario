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
           view.cpp

HEADERS  += mainwindow.h \
            settings.h \
            title.h \
            view.h

FORMS    +=

RESOURCES += \
    mario.qrc

unix|win32: LIBS += -L$$PWD/Lib/ -lAra_About_Dialog

INCLUDEPATH += $$PWD/LibHeader
DEPENDPATH += $$PWD/LibHeader

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/Lib/Ara_About_Dialog.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/Lib/libAra_About_Dialog.a
