QT       += core gui testlib xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

TEMPLATE = lib
DEFINES += SINGLCARCALCULATORCOMPARE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
include(../../3rdlib/ifopt/Ifopt_dependency.pri)
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

SOURCES += \
    singlCarcalculatorCompareActivator.cpp  \
    solvermanager.cpp \
    swarm_ode.cpp \
    jacobiancalc.cpp \
    minimize_topology.cpp



HEADERS += \
    singlCarcalculatorCompareActivator.h \
    solvermanager.h\
    swarm_ode.h \
    jacobiancalc.h \
    minimize_topology.h \
    CommonstructAndfunction.h


