QT       += core gui testlib serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX
include(../../3rdlib/Nlink/NlinkParser.pri)

TEMPLATE = lib
DEFINES += VEHICLE_SWARM_CONTROLLER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    Vehicle_swarm_controllerActivator.cpp \
    device_manager.cpp



HEADERS += \
    Vehicle_swarm_controllerActivator.h \
    device_manager.h


