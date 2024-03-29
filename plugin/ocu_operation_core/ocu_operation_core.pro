QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += OCU_OPERATION_CORE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    batterywidget.cpp \
    mainwindow.cpp \
    menumanager.cpp \
    ocu_operation_coreActivator.cpp \
    statuswidget.cpp \
    titlewidget.cpp \
    viewmanager.cpp



HEADERS += \
    batterywidget.h \
    mainwindow.h \
    menumanager.h \
    ocu_operation_coreActivator.h \
    statuswidget.h \
    titlewidget.h \
    viewmanager.h

RESOURCES += \
    ocu_operation_core_Res.qrc
