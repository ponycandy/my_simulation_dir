QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += PENDULEM_RL_EXPERINECE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    Pendulem_rl_experineceActivator.cpp \
    simmanager.cpp \
    simulator.cpp \
    mypainter.cpp \
    state_file.cpp



HEADERS += \
    Pendulem_rl_experineceActivator.h \
    simmanager.h \
    simulator.h \
    mypainter.h \
    state_file.h


