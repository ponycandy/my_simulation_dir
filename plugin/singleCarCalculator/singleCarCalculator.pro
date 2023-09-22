QT       += core gui testlib xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += SINGLECARCALCULATOR_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build
include(../../3rdlib/ifopt/Ifopt_dependency.pri)

INCLUDEPATH += ../../3rdlib/project_library/src/SwarmAgent
LIBS += -L../../3rdlib/project_library/bin -lSwarmAgent
INCLUDEPATH += ../../3rdlib/project_library/src/ClosePoint
LIBS += -L../../3rdlib/project_library/bin -lClosePoint
INCLUDEPATH += ../../3rdlib/project_library/src/SwarmObstacle
LIBS += -L../../3rdlib/project_library/bin -lSwarmObstacle
INCLUDEPATH += ../../3rdlib/project_library/src/xmlcore
LIBS += -L../../3rdlib/project_library/bin -lxmlcore

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    singleCarCalculatorActivator.cpp \
    solvermanager.cpp \
    swarm_ode.cpp \
    jacobiancalc.cpp \
    minimize_topology.cpp



HEADERS += \
    singleCarCalculatorActivator.h \
    solvermanager.h\
    swarm_ode.h \
    jacobiancalc.h \
    minimize_topology.h \
    CommonstructAndfunction.h


