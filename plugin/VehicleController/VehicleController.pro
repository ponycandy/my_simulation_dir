QT       += core gui testlib network positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += VEHICLECONTROLLER_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build
include(../../3rdlib/GraphicsMapLib/GraphicsMapLib.pri)
include(../../3rdlib/protobuf/protobufdepedency.pri)

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
    VehicleControllerActivator.cpp \
    cardataviewer.cpp \
    singlevehiclecard.cpp \
    vehiclemanager.cpp \
    videoplayer.cpp \
    statusdisplay.cpp \

HEADERS += \
    VehicleControllerActivator.h \
    cardataviewer.h \
    singlevehiclecard.h \
    vehiclemanager.h \
    videoplayer.h \
    statusdisplay.h \
    T30Interface.h \
    remote.pb.h


