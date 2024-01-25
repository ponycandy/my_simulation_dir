QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += VEHICLE_SIMULATOR_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    Vehicle_simulatorActivator.cpp \
    roadmodel.cpp \
    vehicle_manager.cpp \
    simulator.cpp \
    mypainter.cpp \



HEADERS += \
    Vehicle_simulatorActivator.h \
    roadmodel.h \
    vehicle_manager.h \
    simulator.h \
    mypainter.h \



