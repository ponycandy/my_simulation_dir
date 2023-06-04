QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include($$PWD/mkl_Fortrn_dependency.pri)
CONFIG += c++11

TEMPLATE = lib
DEFINES += NONLINEARSOLVER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
INCLUDEPATH += ../../3rdlib/ifopt/ifopt_lib

INCLUDEPATH += ../../3rdlib/project_library/src/Matrix_sparser
LIBS += -L../../3rdlib/project_library/bin -lMatrix_sparser
LIBS += -L../../3rdlib/ifopt/ifopt_lib -lifopt_core
LIBS += -L../../3rdlib/ifopt/ifopt_lib -lifopt_ipopt
INCLUDEPATH+=../../3rdlib/Ipopt
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinmumps
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinmetis
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinhsl
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibipopt

SOURCES += \
    NonlinearSolverActivator.cpp \
    problemconstruct.cpp \
    solvermanager.cpp



HEADERS += \
    NonlinearSolverActivator.h \
    problemconstruct.h \
    solvermanager.h


