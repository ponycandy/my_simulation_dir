QT       += core gui testlib xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
INCLUDEPATH += ../../3rdlib/project_library/src/SmoothSlidingWindowFilter
LIBS += -L../../3rdlib/project_library/bin -lSmoothSlidingWindowFilter
INCLUDEPATH += ../../3rdlib/project_library/src/KalmanFilter
LIBS += -L../../3rdlib/project_library/bin -lKalmanFilter
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += VEHICLE_SWARM_UWB_SIMULATOR_LIBRARY
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
    Vehicle_Swarm_UWB_simulatorActivator.cpp \
    simmanager.cpp \
    vehicle.cpp \
    mypainter.cpp \
    startwindow.cpp



HEADERS += \
    Vehicle_Swarm_UWB_simulatorActivator.h \
    simmanager.h \
    vehicle.h \
    mypainter.h \
    startwindow.h

FORMS += startwindow.ui







