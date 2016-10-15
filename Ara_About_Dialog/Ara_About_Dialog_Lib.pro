#-------------------------------------------------
#
# Project created by QtCreator 2016-10-05T19:42:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ara_About_Dialog

TEMPLATE = lib


SOURCES += main.cpp\
        about_dialog.cpp

HEADERS  += about_dialog.h

FORMS    += about_dialog.ui

CONFIG += c++11 staticlib

RESOURCES += \
    AD_mario.qrc
