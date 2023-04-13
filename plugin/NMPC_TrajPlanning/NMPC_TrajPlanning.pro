QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include($$PWD/mkl_Fortrn_dependency.pri)
CONFIG += c++11

TEMPLATE = lib
DEFINES += NMPC_TRAJPLANNING_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib


INCLUDEPATH+=../../3rdlib/Ipopt
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinmumps
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinmetis
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinhsl
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibipopt







SOURCES += \
    nmpc_problem.cpp \
    nmpc_constructor.cpp \
    NMPC_TrajPlanningActivator.cpp \
    nmpc_manager.cpp


HEADERS += \
    nmpc_problem.h \
    nmpc_constructor.h \
    NMPC_TrajPlanningActivator.h \
    nmpc_manager.h

