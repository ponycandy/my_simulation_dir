QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = lib
DEFINES += TRT_INTERFACE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../

SOURCES += \
    trt_InterfaceActivator.cpp \
    trtmanager.cpp \
    trtui.cpp



HEADERS += \
    trt_InterfaceActivator.h \
    trtmanager.h \
    trtui.h

FORMS += \
    trtui.ui



