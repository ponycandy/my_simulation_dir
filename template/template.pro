QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += PLUGINNAME_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    Activator.cpp



HEADERS += \
    Activator.h


