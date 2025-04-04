QT       += core gui testlib positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17
include(../../3rdlib/GraphicsMapLib/GraphicsMapLib.pri)

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

INCLUDEPATH += ../../3rdlib/Jsonreader


SOURCES += \
    mapmanager.cpp \
    mapwidget.cpp \
    node.cpp \
    ocu_mapActivator.cpp \
    roadmap.cpp



HEADERS += \
    mapmanager.h \
    mapwidget.h \
    node.h \
    ocu_mapActivator.h \
    roadmap.h

FORMS += \
    mapwidget.ui

RESOURCES += map_res.qrc


