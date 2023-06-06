QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = lib
DEFINES += TEST_MPC_NONLINEAR_TRACKING_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    managers.cpp \
    test_MPC_nonlinear_trackingActivator.cpp \
    twotwoode.cpp



HEADERS += \
    managers.h \
    test_MPC_nonlinear_trackingActivator.h \
    twotwoode.h

