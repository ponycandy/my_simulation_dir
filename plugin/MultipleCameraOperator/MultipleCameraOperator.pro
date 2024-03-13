QT       += core gui testlib  xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH += ../../3rdlib/project_library/src/xmlcore
LIBS += -L../../3rdlib/project_library/bin -lxmlcore
CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += MULTIPLECAMERAOPERATOR_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    MultipleCameraOperatorActivator.cpp \
    cameracontroller.cpp \
    cameramanager.cpp



HEADERS += \
    MultipleCameraOperatorActivator.h \
    cameracontroller.h \
    cameramanager.h

FORMS += \
    cameracontroller.ui

RESOURCES += \
    resources.qrc


