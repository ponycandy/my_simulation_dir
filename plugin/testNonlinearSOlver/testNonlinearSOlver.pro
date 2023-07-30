QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../../3rdlib/ifopt/Ifopt_dependency.pri)
CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX
INCLUDEPATH += ../../3rdlib/project_library/src/Matrix_sparser
LIBS += -L../../3rdlib/project_library/bin -lMatrix_sparser

TEMPLATE = lib
DEFINES += TESTNONLINEARSOLVER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    cost_new.cpp \
    terminalset.cpp \
    testNonlinearSOlverActivator.cpp \
    control_widget.cpp \
    main_exe.cpp \
    test_ode.cpp \
    testode_jac.cpp \
    state_file.cpp \
    dynamic_function.cpp \
    jac_mat_file.cpp \
    variable_new.cpp




HEADERS += \
    cost_new.h \
    terminalset.h \
    testNonlinearSOlverActivator.h \
    control_widget.h \
    main_exe.h \
    test_ode.h \
    testode_jac.h \
    state_file.h \
    dynamic_function.h \
    jac_mat_file.h \
    variable_new.h

FORMS += \
    control_widget.ui \


