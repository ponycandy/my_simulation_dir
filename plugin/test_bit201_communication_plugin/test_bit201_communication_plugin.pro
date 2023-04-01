QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = lib
DEFINES += TEST_BIT201_COMMUNICATION_PLUGIN_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../

SOURCES += \
    main_executer.cpp \
    startwidget.cpp \
    test_bit201_communication_pluginActivator.cpp



HEADERS += \
    main_executer.h \
    startwidget.h \
    test_bit201_communication_pluginActivator.h

FORMS += \
    startwidget.ui


