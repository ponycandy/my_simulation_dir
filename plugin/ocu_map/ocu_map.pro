QT       += core gui testlib quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG -= qml_debug
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += OCU_MAP_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib


SOURCES += \
    mapmanager.cpp \
    mapwidget.cpp \
    ocu_mapActivator.cpp



HEADERS += \
    mapmanager.h \
    mapwidget.h \
    ocu_mapActivator.h

FORMS += \
    mapwidget.ui

RESOURCES += \
    map_res.qrc


