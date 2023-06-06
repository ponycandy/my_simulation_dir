QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include($$PWD/mkl_Fortrn_dependency.pri)
include($$PWD/Ifopt_dependency.pri)
CONFIG += c++17

SOURCES += \
    extraconstrain.cpp \
    main.cpp \
    middleclass.cpp \
    test_cost.cpp \
    testcons.cpp \
    testvaiable.cpp

HEADERS += \
    extraconstrain.h \
    middleclass.h \
    test_cost.h \
    testcons.h \
    testvaiable.h

