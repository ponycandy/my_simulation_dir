QT       += core gui testlib xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../../3rdlib/ifopt/Ifopt_dependency.pri)
CONFIG += c++17
CONFIG += console
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += SWARM_PATH_PLANNING_LIBRARY
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
    collision_avoidence.cpp \
    jacobiancalc.cpp \
    minimize_topology.cpp \
    obs_avoidence.cpp \
    planner_manager.cpp \
    swarm_ode.cpp \
    swarm_path_planningActivator.cpp \
    testconstrain.cpp \
    topology_constrain.cpp



HEADERS += \
    CommonstructAndfunction.h \
    collision_avoidence.h \
    jacobiancalc.h \
    minimize_topology.h \
    obs_avoidence.h \
    planner_manager.h \
    swarm_ode.h \
    swarm_path_planningActivator.h \
    testconstrain.h \
    topology_constrain.h


