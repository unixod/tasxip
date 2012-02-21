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
    datadumper.cpp \
    jspluginscontainer.cpp \
    jsplugin.cpp \
    jspluginsloader.cpp

HEADERS  += mainwindow.h \
    dataparser.h \
    rangeset.h \
    datadumper.h \
    pluginsprovider.h \
    jspluginscontainer.h \
    plugin.h \
    jsplugin.h \
    jspluginsloader.h \
    ipv6rangeset.h

FORMS    += mainwindow.ui

DEFINES += VERSION

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    jspluginsloader.js






