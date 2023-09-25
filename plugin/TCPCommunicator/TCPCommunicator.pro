QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

TEMPLATE = lib
DEFINES += TCPCOMMUNICATOR_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX
INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../

SOURCES += \
    TCPCommunicatorActivator.cpp \
    tcpclient.cpp \
    tcpmanager.cpp \
    tcpserverstation.cpp



HEADERS += \
    TCPCommunicatorActivator.h \
    tcpclient.h \
    tcpmanager.h \
    tcpserverstation.h


