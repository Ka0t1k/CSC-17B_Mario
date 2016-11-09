#-------------------------------------------------
#
# Project created by QtCreator 2016-10-07T00:38:03
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ara_Sound_Manager
TEMPLATE = lib


SOURCES += main.cpp\
        ara_sound_manager.cpp

HEADERS  += ara_sound_manager.h

FORMS    += ara_sound_manager.ui

CONFIG += c++11 staticlib

RESOURCES += \
    ara_sound_rsc.qrc
