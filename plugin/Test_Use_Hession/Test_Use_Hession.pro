QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../../3rdlib/ifopt/Ifopt_dependency.pri)
CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += TEST_USE_HESSION_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    Test_Use_HessionActivator.cpp \
    costtermas.cpp \
    managerkl.cpp \
    simpleode.cpp \
    simpleodejacob.cpp



HEADERS += \
    Test_Use_HessionActivator.h \
    costtermas.h \
    managerkl.h \
    simpleode.h \
    simpleodejacob.h


