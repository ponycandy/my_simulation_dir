QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../../3rdlib/gpcs/gpcsdependency.pri)

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += SLAM_VISUALIZER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    Slam_VisualizerActivator.cpp \
    controlpanel.cpp \
    slam_drawer.cpp \
    vomanager.cpp



HEADERS += \
    Slam_VisualizerActivator.h \
    controlpanel.h \
    slam_drawer.h \
    vomanager.h

FORMS += \
    controlpanel.ui


