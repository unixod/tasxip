#-------------------------------------------------
#
# Project created by QtCreator 2012-02-19T14:12:19
#
#-------------------------------------------------

QT       += script testlib

QT       -= gui

TARGET = tst_jspluginsloader
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_jspluginsloader.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

#tasxip depend
DEPENDPATH += $$PWD/../../tasxip
INCLUDEPATH += $$PWD/../../tasxip
SOURCES += jspluginsloader.cpp
RESOURCES += resources.qrc \
    tstplugins.qrc

OTHER_FILES += \
    minimum_plg.js \
    multi_plg.js

INCLUDEPATH += $$PWD/../../uau
DEPENDPATH += $$PWD/../../uau
QMAKE_CXXFLAGS += -std=c++0x
