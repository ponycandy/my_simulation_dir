QT       += core gui testlib xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include($$PWD/Ifopt_dependency.pri)
CONFIG += c++17


INCLUDEPATH += ../../3rdlib/project_library/src/Matrix_sparser
LIBS += -L../../3rdlib/project_library/bin -lMatrix_sparser
INCLUDEPATH += ../../3rdlib/project_library/src/xmlcore
LIBS += -L../../3rdlib/project_library/bin -lxmlcore
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += SWARM_NMPC_PLANNER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    Swarm_NMPC_PlannerActivator.cpp \
    controlconstrain.cpp \
    dynamics_constrain.cpp \
    dynamics_of_animals.cpp \
    jacobian_state.cpp \
    problem_wrapup.cpp \
    solver_manager.cpp \
    splinevariable.cpp \
    state_variable.cpp \
    testpolyparams.cpp \
    PolyParams.cpp



HEADERS += \
    Swarm_NMPC_PlannerActivator.h \
    controlconstrain.h \
    dynamics_constrain.h \
    dynamics_of_animals.h \
    jacobian_state.h \
    problem_wrapup.h \
    solver_manager.h \
    splinevariable.h \
    state_variable.h \
    testpolyparams.h \
    var_packer.h \
    PolyParams.h









































