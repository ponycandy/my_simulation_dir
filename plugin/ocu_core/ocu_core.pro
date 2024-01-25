QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += OCU_CORE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    coremainwindow.cpp \
    coreviewmanager.cpp \
    ocu_coreActivator.cpp



HEADERS += \
    coremainwindow.h \
    coreviewmanager.h \
    ocu_coreActivator.h



