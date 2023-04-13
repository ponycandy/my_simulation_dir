QT       += core gui testlib network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#备注，所有的节点都是等权的，所有连接都连接到中心节点上，再连接到目标位置
#反正只是做自组网的仿真，这样的灵活度就已经足够了
CONFIG += c++11

TEMPLATE = lib
DEFINES += TCPAUTONET_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../

SOURCES += \
    TCPAutoNetActivator.cpp \
    tcpautonetmanager.cpp \
    tcpserverstation.cpp



HEADERS += \
    TCPAutoNetActivator.h \
    tcpautonetmanager.h \
    tcpserverstation.h


