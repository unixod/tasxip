#-------------------------------------------------
#
# Project created by QtCreator 2011-07-17T17:40:19
#
#-------------------------------------------------

QT       += core gui network script

TARGET = tasxip
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainwindow_net.cpp \
    dataparser.cpp \
    jspluginscontainer.cpp \
    jsplugin.cpp \
    jspluginsloader.cpp \
    pluginsengine.cpp \
    plugininfodlg.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    dataparser.h \
    pluginsprovider.h \
    jspluginscontainer.h \
    plugin.h \
    jsplugin.h \
    jspluginsloader.h \
    pluginsengine.h \
    plugininfodlg.h \
    settings.h

FORMS    += mainwindow.ui \
    plugininfodlg.ui

DEFINES += VERSION

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    jspluginsloader.js \
    basicplugin.js \
    default.cfg

INCLUDEPATH += $$PWD/../uau
DEPENDPATH += $$PWD/../uau
QMAKE_CXXFLAGS += -std=c++0x





