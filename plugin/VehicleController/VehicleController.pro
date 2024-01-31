QT       += core gui testlib network positioning openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += VEHICLECONTROLLER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build
include(../../3rdlib/mqtt/mqtt.pri)
INCLUDEPATH += ../../3rdlib/project_library/src/GraphicsMapLib
LIBS += -L../../3rdlib/project_library/bin -lGraphicsMapLib
INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    VehicleControllerActivator.cpp \
    cardataviewer.cpp \
    singlevehiclecard.cpp \
    vehiclemanager.cpp \
    videoplayer.cpp




HEADERS += \
    VehicleControllerActivator.h \
    cardataviewer.h \
    singlevehiclecard.h \
    vehiclemanager.h \
    videoplayer.h

FORMS += \
    cardataviewer.ui


