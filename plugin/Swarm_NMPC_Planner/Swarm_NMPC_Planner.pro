QT       += core gui testlib xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../../3rdlib/ifopt/Ifopt_dependency.pri)
include(../../3rdlib/ATGlib/ATGlib_dependency.pri)
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
    automated_gradient.cpp \
    controlconstrain.cpp \
    dynamics_constrain.cpp \
    dynamics_of_animals.cpp \
    jacobian_state.cpp \
    minimize_speed_cost.cpp \
    problem_wrapup.cpp \
    solver_manager.cpp \
    splinevariable.cpp \
    startdreaw.cpp \
    state_variable.cpp \
    terminalwithinrange.cpp \
    testpolyparams.cpp \
    PolyParams.cpp \
    trackingcost.cpp \
    visualizer.cpp \
    mass_center_constrain.cpp



HEADERS += \
    Swarm_NMPC_PlannerActivator.h \
    automated_gradient.h \
    controlconstrain.h \
    dynamics_constrain.h \
    dynamics_of_animals.h \
    jacobian_state.h \
    minimize_speed_cost.h \
    problem_wrapup.h \
    solver_manager.h \
    splinevariable.h \
    startdreaw.h \
    state_variable.h \
    terminalwithinrange.h \
    testpolyparams.h \
    trackingcost.h \
    var_packer.h \
    PolyParams.h \
    visualizer.h \
    mass_center_constrain.h

FORMS += \
    startdreaw.ui











































