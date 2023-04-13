QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qt
CONFIG += c++11

TEMPLATE = lib
DEFINES += TEST_NMPC_PLUGIN_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    control_widget.cpp \
    main_exe.cpp \
    test_NMPC_PluginActivator.cpp \
    test_ode.cpp \
    testode_jac.cpp



HEADERS += \
    control_widget.h \
    main_exe.h \
    test_NMPC_PluginActivator.h \
    test_ode.h \
    testode_jac.h

FORMS += \
    control_widget.ui


