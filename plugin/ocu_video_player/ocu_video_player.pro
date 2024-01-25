QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../../3rdlib/FFmpeg/FFmpegdepedency.pri)
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
    ocu_video_playerActivator.cpp \
    imagedisplay.cpp \
    ./avplayer/avdecoder.cpp   \
    ./avplayer/avplayer.cpp \
    video_display_widget.cpp \
    video_manager.cpp


HEADERS += \
    ocu_video_playerActivator.h \
    imagedisplay.h \
    ./avplayer/avdecoder.h   \
    ./avplayer/avplayer.h \
    video_display_widget.h \
    video_manager.h

FORMS += \
    video_display_widget.ui

RESOURCES += \
    imgsrc.qrc
