QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console



TEMPLATE = lib
DEFINES += COLLISIONDETECT_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../3rdlib
INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../

SOURCES += \
    CollisionDetectActivator.cpp \
    collisioncalculator.cpp



HEADERS += \
    CollisionDetectActivator.h \
    collisioncalculator.h







