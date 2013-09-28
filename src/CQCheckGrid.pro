TEMPLATE = lib

TARGET = 

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
