QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
INCLUDEPATH += ../../3rdlib/project_library/src/ClosePoint
LIBS += -L../../3rdlib/project_library/bin -lClosePoint
INCLUDEPATH += ../../3rdlib/project_library/src/SwarmAgent
LIBS += -L../../3rdlib/project_library/bin -lSwarmAgent
#INCLUDEPATH +=../../3rdlib/project_library/include/classA_test
#LIBS += -L../../3rdlib/project_library/bin -lclassA_test

TEMPLATE = lib
DEFINES += JOY_CARD_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = ../../build
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX

INCLUDEPATH += ../../build/config
INCLUDEPATH += ../../include
INCLUDEPATH += ../../
INCLUDEPATH += ../../3rdlib

SOURCES += \
    JOY_cardActivator.cpp \
    main_stream.cpp \
    mypainter.cpp \
    simulator.cpp \



HEADERS += \
    JOY_cardActivator.h \
    main_stream.h \
    mypainter.h \
    simulator.h \








