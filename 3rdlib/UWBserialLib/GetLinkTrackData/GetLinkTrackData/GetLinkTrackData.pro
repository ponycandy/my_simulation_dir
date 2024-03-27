QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    nlink_linktrack_anchorframe0.c \
    nlink_linktrack_aoa_nodeframe0.c \
    nlink_linktrack_nodeframe0.c \
    nlink_linktrack_nodeframe1.c \
    nlink_linktrack_nodeframe2.c \
    nlink_linktrack_nodeframe3.c \
    nlink_linktrack_nodeframe5.c \
    nlink_linktrack_nodeframe6.c \
    nlink_linktrack_tagframe0.c \
    nlink_tofsense_frame0.c \
    nlink_utils.c

HEADERS += \
    mainwindow.h \
    nlink_linktrack_anchorframe0.h \
    nlink_linktrack_aoa_nodeframe0.h \
    nlink_linktrack_nodeframe0.h \
    nlink_linktrack_nodeframe1.h \
    nlink_linktrack_nodeframe2.h \
    nlink_linktrack_nodeframe3.h \
    nlink_linktrack_nodeframe5.h \
    nlink_linktrack_nodeframe6.h \
    nlink_linktrack_tagframe0.h \
    nlink_tofsense_frame0.h \
    nlink_utils.h \
    nlink_typedef.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


