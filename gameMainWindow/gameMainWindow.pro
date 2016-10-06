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


SOURCES += main.cpp\
           mainwindow.cpp \
           settings.cpp \
    title.cpp

HEADERS  += mainwindow.h \
            settings.h \
    title.h

FORMS    +=

RESOURCES += \
    mario.qrc
