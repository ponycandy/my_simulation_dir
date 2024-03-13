QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += OCU_VIDEO_PLAYER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    crossaxle.cpp \
    ocu_video_playerActivator.cpp \
    video_display_widget.cpp \
    video_manager.cpp \
    batterystatus.cpp \
    customslider.cpp \
    directionhron.cpp \
    hronslider.cpp \


HEADERS += \
    crossaxle.h \
    ocu_video_playerActivator.h \
    video_display_widget.h \
    video_manager.h \
    batterystatus.h \
    customslider.h \
    directionhron.h \
    hronslider.h \

RESOURCES += \
    imgsrc.qrc
