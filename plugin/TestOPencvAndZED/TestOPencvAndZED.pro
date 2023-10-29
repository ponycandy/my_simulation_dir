QT       += core gui testlib opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX
include (../../3rdlib/ZED/ZEDDepend.pri)

TEMPLATE = lib
DEFINES += TESTOPENCVANDZED_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    TestOPencvAndZEDActivator.cpp \
    cubedrawer.cpp \
    pointclouddrawer.cpp \
    testcuda.cpp \
    zedviewer.cpp



HEADERS += \
    TestOPencvAndZEDActivator.h \
    cubedrawer.h \
    pointclouddrawer.h \
    testcuda.h \
    zedviewer.h


