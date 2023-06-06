QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include($$PWD/mkl_Fortrn_dependency.pri)
include($$PWD/Ifopt_dependency.pri)
CONFIG += c++11

TEMPLATE = lib
DEFINES += TESTIFOPT_2_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../

SOURCES += \
    testifopt_2Activator.cpp



HEADERS += \
    testifopt_2Activator.h


