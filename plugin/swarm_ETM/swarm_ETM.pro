QT       += core gui testlib xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



INCLUDEPATH += ../../3rdlib/project_library/src/SwarmObstacle
LIBS += -L../../3rdlib/project_library/bin -lSwarmObstacle
INCLUDEPATH += ../../3rdlib/project_library/src/SwarmAgent
LIBS += -L../../3rdlib/project_library/bin -lSwarmAgent
INCLUDEPATH += ../../3rdlib/project_library/src/ClosePoint
LIBS += -L../../3rdlib/project_library/bin -lClosePoint
INCLUDEPATH += ../../3rdlib/project_library/src/xmlcore
LIBS += -L../../3rdlib/project_library/bin -lxmlcore

INCLUDEPATH += ../../3rdlib/project_library/src/DeadReckon
LIBS += -L../../3rdlib/project_library/bin -lDeadReckon


CONFIG += c++17
CONFIG += console


QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += SWARM_ETM_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build




INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    swarm_ETMActivator.cpp \
    testtriggered.cpp \
    vehicle.cpp \
    simmanager.cpp \
    mypainter.cpp



HEADERS += \
    swarm_ETMActivator.h \
    testtriggered.h \
    vehicle.h \
    simmanager.h \
    mypainter.h

FORMS += \
    testtriggered.ui






