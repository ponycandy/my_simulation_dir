QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../../3rdlib/gpcs/gpcsdependency.pri)
CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += TEST_USING_GPCS_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../

SOURCES += \
    Test_using_gpcsActivator.cpp \
    controlwidget.cpp \
    mainexecution.cpp



HEADERS += \
    Test_using_gpcsActivator.h \
    controlwidget.h \
    mainexecution.h

FORMS += \
    controlwidget.ui


