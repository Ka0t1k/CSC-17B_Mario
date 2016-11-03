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
    placeholderscene.cpp

HEADERS  += mainwindow.h \
            settings.h \
            title.h \
            view.h \
    placeholderscene.h

FORMS    +=

RESOURCES += \
    mario.qrc

win32: LIBS += -L$$PWD/WinLib/ -lAra_About_Dialog

INCLUDEPATH += $$PWD/LibHeaders
DEPENDPATH += $$PWD/LibHeaders

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/WinLib/Ara_About_Dialog.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/WinLib/libAra_About_Dialog.a

macx: LIBS += -L$$PWD/MacLib/ -lAra_About_Dialog
macx: PRE_TARGETDEPS += $$PWD/MacLib/libAra_About_Dialog.a