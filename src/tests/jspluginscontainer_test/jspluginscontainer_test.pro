#-------------------------------------------------
#
# Project created by QtCreator 2012-02-19T19:05:40
#
#-------------------------------------------------

QT       += script testlib

QT       -= gui

TARGET = tst_jspluginscontainer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_jspluginscontainer.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

#tasxip depend
DEPENDPATH += $$PWD/../../tasxip
INCLUDEPATH += $$PWD/../../tasxip
SOURCES += jspluginsloader.cpp \
        jspluginscontainer.cpp \
        jsplugin.cpp
RESOURCES += resources.qrc \
    $$PWD/../jspluginsloader_test/tstplugins.qrc    #test plugins from jspluginsloader_test

#OTHER_FILES += \
#    minimum_plg.js \
#    multi_plg.js

INCLUDEPATH += $$PWD/../../uau
DEPENDPATH += $$PWD/../../uau
QMAKE_CXXFLAGS += -std=c++0x
