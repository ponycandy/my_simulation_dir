QT       += core gui testlib openglwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += ANIMATOR3D_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../

SOURCES += \
    Animator3DActivator.cpp \
    base_widget.cpp \
    glpainter3d.cpp \
    glwidget3d.cpp



HEADERS += \
    Animator3DActivator.h \
    base_widget.h \
    glpainter3d.h \
    glwidget3d.h

FORMS += \
    base_widget.ui


