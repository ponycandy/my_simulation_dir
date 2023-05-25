QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TEMPLATE = lib
DEFINES += PUSHINGBOX_2D_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX
INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    pushingbox_2dActivator.cpp \
    simmanager.cpp \
simulator.cpp \
mypainter.cpp



HEADERS += \
    pushingbox_2dActivator.h \
    simmanager.h \
simulator.h \
mypainter.h


