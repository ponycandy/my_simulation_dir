CONFIG += c++20
INCLUDEPATH += ../../3rdlib/Nlink
INCLUDEPATH += ../../3rdlib

SOURCES += \
   ../../3rdlib/Nlink/nlink_utils.cpp \
  ../../3rdlib/Nlink/nlink_linktrack_nodeframe0.cpp \
  ../../3rdlib/Nlink/nlink_linktrack_nodeframe1.cpp \
  ../../3rdlib/Nlink/nlink_linktrack_nodeframe2.cpp \
  ../../3rdlib/Nlink/nlink_linktrack_nodeframe3.cpp \
  ../../3rdlib/Nlink/nlink_linktrack_aoa_nodeframe0.cpp \
  ../../3rdlib/Nlink/nlink_linktrack_tagframe0.cpp \
  ../../3rdlib/Nlink/nlink_linktrack_anchorframe0.cpp \
  ../../3rdlib/Nlink/nlink_tofsense_frame0.cpp \
  ../../3rdlib/Nlink/nlink_tofsensem_frame0.cpp

HEADERS += \
   ../../3rdlib/Nlink/nlink_iot_frame0.h \
    ../../3rdlib/Nlink/nlink_linktrack_anchorframe0.h \
    ../../3rdlib/Nlink/nlink_linktrack_aoa_nodeframe0.h \
    ../../3rdlib/Nlink/nlink_linktrack_nodeframe0.h \
    ../../3rdlib/Nlink/nlink_linktrack_nodeframe1.h \
    ../../3rdlib/Nlink/nlink_linktrack_nodeframe2.h   \
    ../../3rdlib/Nlink/nlink_linktrack_nodeframe3.h \
    ../../3rdlib/Nlink/nlink_linktrack_nodeframe4.h \
    ../../3rdlib/Nlink/nlink_linktrack_nodeframe5.h \
    ../../3rdlib/Nlink/nlink_linktrack_nodeframe6.h \
    ../../3rdlib/Nlink/nlink_linktrack_tagframe0.h \
    ../../3rdlib/Nlink/nlink_tofsensem_frame0.h \
    ../../3rdlib/Nlink/nlink_tofsense_frame0.h \
    ../../3rdlib/Nlink/nlink_typedef.h \
   ../../3rdlib/Nlink/nlink_utils.h

