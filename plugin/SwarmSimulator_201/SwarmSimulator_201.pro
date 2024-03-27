QT       += core gui testlib xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

INCLUDEPATH += ../../3rdlib/project_library/src/SwarmAgent
LIBS += -L../../3rdlib/project_library/bin -lSwarmAgent
INCLUDEPATH += ../../3rdlib/project_library/src/ClosePoint
LIBS += -L../../3rdlib/project_library/bin -lClosePoint
INCLUDEPATH += ../../3rdlib/project_library/src/SwarmObstacle
LIBS += -L../../3rdlib/project_library/bin -lSwarmObstacle
INCLUDEPATH += ../../3rdlib/project_library/src/xmlcore
LIBS += -L../../3rdlib/project_library/bin -lxmlcore

TEMPLATE = lib
DEFINES += SWARMSIMULATOR_201_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib
SOURCES += \
    SwarmSimulator_201Activator.cpp \
    simulator_manager.cpp \
    simulator.cpp \



HEADERS += \
    SwarmSimulator_201Activator.h \
    simulator_manager.h \
    simulator.h \


