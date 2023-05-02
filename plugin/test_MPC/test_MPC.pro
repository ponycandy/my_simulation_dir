QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = lib
DEFINES += TEST_MPC_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    dynamic_function.cpp \
    form.cpp \
    mainexec.cpp \
    test_MPCActivator.cpp \
    myfile.cpp \
    state_file.cpp



HEADERS += \
    dynamic_function.h \
    form.h \
    mainexec.h \
    test_MPCActivator.h \
    myfile.h \
    state_file.h

FORMS += \
    form.ui


