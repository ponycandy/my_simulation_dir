QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += OCU_CAR_MANAGER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    ocu_car_managerActivator.cpp \
    startwindow.cpp \
    viewmanager.cpp \
    whitewidget.cpp \
    situationalplan.cpp



HEADERS += \
    ocu_car_managerActivator.h \
    startwindow.h \
    viewmanager.h \
    whitewidget.h \
    situationalplan.h

FORMS += \
    startwindow.ui \
    whitewidget.ui

RESOURCES += iconresource.qrc


