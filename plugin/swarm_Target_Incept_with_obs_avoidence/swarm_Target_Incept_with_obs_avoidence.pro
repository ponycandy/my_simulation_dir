QT       += core gui testlib xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += SWARM_TARGET_INCEPT_WITH_OBS_AVOIDENCE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build


INCLUDEPATH += ../../3rdlib/project_library/src/SwarmObstacle
LIBS += -L../../3rdlib/project_library/bin -lSwarmObstacle
INCLUDEPATH += ../../3rdlib/project_library/src/SwarmAgent
LIBS += -L../../3rdlib/project_library/bin -lSwarmAgent
INCLUDEPATH += ../../3rdlib/project_library/src/ClosePoint
LIBS += -L../../3rdlib/project_library/bin -lClosePoint
INCLUDEPATH += ../../3rdlib/project_library/src/xmlcore
LIBS += -L../../3rdlib/project_library/bin -lxmlcore


INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    swarm_Target_Incept_with_obs_avoidenceActivator.cpp \
    simmanager.cpp \
    vehicle.cpp \
    mypainter.cpp \



HEADERS += \
    swarm_Target_Incept_with_obs_avoidenceActivator.h \
    simmanager.h \
    vehicle.h \
    mypainter.h \




