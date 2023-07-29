QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../../3rdlib/ATGlib/ATGlib_dependency.pri)
include($$PWD/Ifopt_dependency.pri)
CONFIG += console
CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += TESTAUTOGRAD_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    costfunc.cpp \
    testautogradActivator.cpp \
    testmain.cpp \
    variablexl.cpp



HEADERS += \
    costfunc.h \
    testautogradActivator.h \
    testmain.h \
    variablexl.h


