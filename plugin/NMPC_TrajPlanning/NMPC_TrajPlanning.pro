QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include($$PWD/mkl_Fortrn_dependency.pri)
CONFIG += c++17
CONFIG += console
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX
INCLUDEPATH += ../../3rdlib/project_library/src/Matrix_sparser
LIBS += -L../../3rdlib/project_library/bin -lMatrix_sparser

TEMPLATE = lib
DEFINES += NMPC_TRAJPLANNING_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib










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



