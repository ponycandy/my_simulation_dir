QT       += core gui testlib positioning openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../../3rdlib/GraphicsMapLib/GraphicsMapLib.pri)

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += TESTFFMPEGUTILITY_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

# INCLUDEPATH += ../../3rdlib/project_library/src/GraphicsMapLib
# LIBS += -L../../3rdlib/project_library/bin -lGraphicsMapLib

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    form.cpp \
    testffmpegutilityActivator.cpp



HEADERS += \
    form.h \
    testffmpegutilityActivator.h

FORMS += \
    form.ui


