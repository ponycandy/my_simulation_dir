QT       += core gui testlib xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../../3rdlib/ifopt/Ifopt_dependency.pri)

CONFIG += c++17
CONFIG += console
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += SWARM_PATH_PLANNING_FEEDBACK_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build


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
    nonlinearplanner.cpp \
    swarm_path_planning_FeedBackActivator.cpp \
    simmanager.cpp \
    vehicle.cpp \
    mypainter.cpp \
    swarm_ode.cpp \
    jacobiancalc.cpp \
    minimize_topology.cpp



HEADERS += \
    nonlinearplanner.h \
    swarm_path_planning_FeedBackActivator.h \
    simmanager.h \
    vehicle.h \
    mypainter.h \
    swarm_ode.h \
    jacobiancalc.h \
    minimize_topology.h \
    CommonstructAndfunction.h


