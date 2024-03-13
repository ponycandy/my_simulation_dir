QT       += core gui testlib network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

include(../../3rdlib/mqtt/mqtt.pri)

TEMPLATE = lib
DEFINES += TESTMULTITOPICSUBSCRIBE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    mqttmanager.cpp \
    testmultitopicsubscribeActivator.cpp



HEADERS += \
    mqttmanager.h \
    testmultitopicsubscribeActivator.h


