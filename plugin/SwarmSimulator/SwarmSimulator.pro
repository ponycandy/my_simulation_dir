QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
INCLUDEPATH += ../../3rdlib/project_library/src/SwarmAgent
LIBS += -L../../3rdlib/project_library/bin -lSwarmAgent
INCLUDEPATH += ../../3rdlib/project_library/src/ClosePoint
LIBS += -L../../3rdlib/project_library/bin -lClosePoint
INCLUDEPATH += ../../3rdlib/project_library/src/SwarmObstacle
LIBS += -L../../3rdlib/project_library/bin -lSwarmObstacle


TEMPLATE = lib
DEFINES += SWARMSIMULATOR_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    SwarmSimulatorActivator.cpp \
    simulator_manager.cpp \
    mypainter.cpp \
    simulator.cpp \



HEADERS += \
    SwarmSimulatorActivator.h \
    simulator_manager.h \
    mypainter.h \
    simulator.h \














