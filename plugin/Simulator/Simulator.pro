QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = lib
DEFINES += SIMULATOR_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../

SOURCES += \
    SimulatorActivator.cpp \
    simer.cpp \
    simulatormanager.cpp



HEADERS += \
    SimulatorActivator.h \
    simer.h \
    simulatormanager.h


