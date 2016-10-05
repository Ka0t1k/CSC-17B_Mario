
QT += widgets

TEMPLATE = app
TARGET = testsprite
DEPENDPATH += .
INCLUDEPATH += .
RESOURCES += testsprite.qrc

# Input
SOURCES += main.cpp \
    gamecanvas.cpp \
    sprite.cpp
HEADERS += gamecanvas.h \
    sprite.h
