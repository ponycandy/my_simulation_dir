QT       += core gui testlib  positioning openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += OCU_CAR_MANAGER_SIM_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build
INCLUDEPATH += ../../3rdlib/project_library/src/GraphicsMapLib
LIBS += -L../../3rdlib/project_library/bin -lGraphicsMapLib
INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    controlmodeswitchwidget.cpp \
    devicecontrol.cpp \
    multistatusslider.cpp \
    ocu_car_manager_simActivator.cpp \
    simulationconfiguration.cpp \
    situationalplan.cpp \
    startwindow.cpp \
    videomanager.cpp \
    viewmanager.cpp \
    whitewidget.cpp



HEADERS += \
    controlmodeswitchwidget.h \
    devicecontrol.h \
    multistatusslider.h \
    ocu_car_manager_simActivator.h \
    simulationconfiguration.h \
    situationalplan.h \
    startwindow.h \
    videomanager.h \
    viewmanager.h \
    whitewidget.h

FORMS += \
    startwindow.ui \
    whitewidget.ui

RESOURCES += iconresource.qrc
