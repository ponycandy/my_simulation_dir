QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include (../../3rdlib/Opencv/OpencvDepend.pri)

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += TEST_VISUAL_ODOMETRY_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../

SOURCES += \
    Test_Visual_OdometryActivator.cpp \
    camera.cpp \
    frame.cpp \
    map.cpp \
    mappoints.cpp \
    system.cpp \
    viewer.cpp \
    visual_odometry.cpp



HEADERS += \
    Test_Visual_OdometryActivator.h \
    camera.h \
    common_include.h \
    frame.h \
    map.h \
    mappoints.h \
    system.h \
    viewer.h \
    visual_odometry.h


