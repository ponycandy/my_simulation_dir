QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += SWARM_NMPC_TRAJECTORY_PLANNER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../

SOURCES += \
    swarm_NMPC_trajectory_plannerActivator.cpp



HEADERS += \
    swarm_NMPC_trajectory_plannerActivator.h


