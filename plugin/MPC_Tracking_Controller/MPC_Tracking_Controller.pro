QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include($$PWD/osqp_eigen_dependency.pri)
CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX
INCLUDEPATH += ../../3rdlib/project_library/src/Matrix_sparser
LIBS += -L../../3rdlib/project_library/bin -lMatrix_sparser
INCLUDEPATH += ../../3rdlib/project_library/src/Matrix_sparser
LIBS += -L../../3rdlib/project_library/bin -lMatrix_sparser

TEMPLATE = lib
DEFINES += MPC_TRACKING_CONTROLLER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH+=../../3rdlib/osqp
LIBS +=   -L../../3rdlib/osqp/ -losqp


INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    MPC_Tracking_ControllerActivator.cpp \
    mpc_constructor.cpp \
    mpc_manager.cpp \




HEADERS += \
    MPC_Tracking_ControllerActivator.h \
    mpc_constructor.h \
    mpc_manager.h \




