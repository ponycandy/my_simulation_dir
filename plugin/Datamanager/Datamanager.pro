QT       += core gui testlib xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

INCLUDEPATH += ../../3rdlib/project_library/src/xmlcore
LIBS += -L../../3rdlib/project_library/bin -lxmlcore

TEMPLATE = lib
DEFINES += DATAMANAGER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    DatamanagerActivator.cpp \
    datacollection.cpp \
    messagecollector.cpp \
    netconfigwidget.cpp



HEADERS += \
    DatamanagerActivator.h \
    datacollection.h \
    messagecollector.h \
    netconfigwidget.h

FORMS += \
    netconfigwidget.ui

