QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include($$PWD/mkl_Fortrn_dependency.pri)
include($$PWD/Ifopt_dependency.pri)

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX
TEMPLATE = lib

DEFINES += NONLINEARSOLVER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib


INCLUDEPATH += ../../3rdlib/project_library/src/Matrix_sparser
LIBS += -L../../3rdlib/project_library/bin -lMatrix_sparser

INCLUDEPATH+=../../3rdlib/Ipopt
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinmumps
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinmetis
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinhsl
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibipopt

SOURCES += \
    NonlinearSolverActivator.cpp \
    solvermanager.cpp \
        problemconstruct.cpp \
    dynamics_constrain_set.cpp \
    dynamics_cost_set.cpp \
    dynamics_varaible_set.cpp \





HEADERS += \
    NonlinearSolverActivator.h \
    solvermanager.h \
    problemconstruct.h \
    dynamics_constrain_set.h \
    dynamics_cost_set.h \
    dynamics_varaible_set.h \

DISTFILES += \
    关于本组件的bug的说明




