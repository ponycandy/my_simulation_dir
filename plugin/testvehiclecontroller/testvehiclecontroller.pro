QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../../3rdlib/gpcs/gpcsdependency.pri)

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += TESTVEHICLECONTROLLER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    controllerwidget.cpp \
    messagemanager.cpp \
    testvehiclecontrollerActivator.cpp



HEADERS += \
    controllerwidget.h \
    messagemanager.h \
    testvehiclecontrollerActivator.h

FORMS += \
    controllerwidget.ui




