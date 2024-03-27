QT       += core gui testlib xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../../3rdlib/GraphicsMapLib/GraphicsMapLib.pri)

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += VISUALIZER_201_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build
INCLUDEPATH += ../../3rdlib/project_library/src/SwarmAgent
LIBS += -L../../3rdlib/project_library/bin -lSwarmAgent
INCLUDEPATH += ../../3rdlib/project_library/src/ClosePoint
LIBS += -L../../3rdlib/project_library/bin -lClosePoint
INCLUDEPATH += ../../3rdlib/project_library/src/SwarmObstacle
LIBS += -L../../3rdlib/project_library/bin -lSwarmObstacle
INCLUDEPATH += ../../3rdlib/project_library/src/xmlcore
LIBS += -L../../3rdlib/project_library/bin -lxmlcore

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    Visualizer_201Activator.cpp \
    animator_manager.cpp \
    controlwidget.cpp \
    eventediter.cpp \
    myanimator.cpp \
    vehicle.cpp



HEADERS += \
    Visualizer_201Activator.h \
    animator_manager.h \
    controlwidget.h \
    eventediter.h \
    myanimator.h \
    vehicle.h

RESOURCES += map_res.qrc

