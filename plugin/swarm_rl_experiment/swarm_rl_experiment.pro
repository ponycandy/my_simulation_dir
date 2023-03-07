QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
INCLUDEPATH += ../../3rdlib/project_library/src/ClosePoint
LIBS += -L../../3rdlib/project_library/bin -lClosePoint
INCLUDEPATH += ../../3rdlib/project_library/src/SwarmAgent
LIBS += -L../../3rdlib/project_library/bin -lSwarmAgent

TEMPLATE = lib
DEFINES += SWARM_RL_EXPERIMENT_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib


SOURCES += \
    simulatorwidget.cpp \
    swarm_rl_experimentActivator.cpp \
    main_stream.cpp \
    vehicle.cpp



HEADERS += \
    simulatorwidget.h \
    swarm_rl_experimentActivator.h \
    main_stream.h \
    vehicle.h

FORMS += \
    simulatorwidget.ui






