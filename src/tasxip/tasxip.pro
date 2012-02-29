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
    plugininfodlg.cpp

HEADERS  += mainwindow.h \
    dataparser.h \
    rangeset.h \
    pluginsprovider.h \
    jspluginscontainer.h \
    plugin.h \
    jsplugin.h \
    jspluginsloader.h \
    ipv6rangeset.h \
    pluginsengine.h \
    plugininfodlg.h

FORMS    += mainwindow.ui \
    plugininfodlg.ui

DEFINES += VERSION

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    jspluginsloader.js \
    basicplugin.js






