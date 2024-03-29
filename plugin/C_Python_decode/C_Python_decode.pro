QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

TEMPLATE = lib
DEFINES += C_PYTHON_DECODE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    C_Python_decodeActivator.cpp \
    cpydevoder.cpp \
    decoder_manager.cpp



HEADERS += \
    C_Python_decodeActivator.h \
    cpydevoder.h \
    decoder_manager.h


