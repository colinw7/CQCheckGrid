TEMPLATE = app

TARGET =  CQCheckGridTest

QT += widgets

DEPENDPATH += .

#CONFIG += debug

# Input
SOURCES += \
CQCheckGridTest.cpp \

HEADERS += \
CQCheckGridTest.h \

DESTDIR     = .
OBJECTS_DIR = .

INCLUDEPATH += \
../include \
.

unix:LIBS += \
-L../lib \
-lCQCheckGrid
