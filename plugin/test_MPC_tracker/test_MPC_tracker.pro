QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console

TEMPLATE = lib
DEFINES += TEST_MPC_TRACKER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    form.cpp \
    mainexe.cpp \
    test_MPC_trackerActivator.cpp \
    dynamic_function.cpp



HEADERS += \
    form.h \
    mainexe.h \
    test_MPC_trackerActivator.h \
    dynamic_function.h

FORMS += \
    form.ui


