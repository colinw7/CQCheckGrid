TEMPLATE = lib

TARGET = CQCheckGrid

QT += widgets

DEPENDPATH += .

CONFIG += staticlib

# Input
HEADERS += \
../include/CQCheckGrid.h \

SOURCES += \
CQCheckGrid.cpp \

OBJECTS_DIR = ../obj

DESTDIR = ../lib

INCLUDEPATH += \
. \
../include \
