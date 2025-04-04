QT += positioning

#LIBS += -L../../3rdlib/GraphicsMapLib/lib -lGraphicsMapLibd
INCLUDEPATH += ../../3rdlib/GraphicsMapLib/src
SOURCES += \
    ../../3rdlib/GraphicsMapLib/src/interactivemap.cpp \
   ../../3rdlib/GraphicsMapLib/src/graphicsmap.cpp \
     ../../3rdlib/GraphicsMapLib/src/mapellipseitem.cpp \
     ../../3rdlib/GraphicsMapLib/src/maplabelitem.cpp \
     ../../3rdlib/GraphicsMapLib/src/maplineitem.cpp    \
      ../../3rdlib/GraphicsMapLib/src/mapobjectitem.cpp \
      ../../3rdlib/GraphicsMapLib/src/mapoperator.cpp \
      ../../3rdlib/GraphicsMapLib/src/mappieitem.cpp \
       ../../3rdlib/GraphicsMapLib/src/mappolygonitem.cpp \
       ../../3rdlib/GraphicsMapLib/src/maprangeringitem.cpp \
       ../../3rdlib/GraphicsMapLib/src/maprouteitem.cpp \
        ../../3rdlib/GraphicsMapLib/src/maptrailitem.cpp \
        ../../3rdlib/GraphicsMapLib/src/maprectitem.cpp \
         ../../3rdlib/GraphicsMapLib/src/maptableitem.cpp \
         ../../3rdlib/GraphicsMapLib/src/mapscutcheonitem.cpp\
         ../../3rdlib/GraphicsMapLib/src/mappathitem.cpp\

HEADERS += \
../../3rdlib/GraphicsMapLib/src/interactivemap.h \
../../3rdlib/GraphicsMapLib/src/mapellipseitem.h \
 ../../3rdlib/GraphicsMapLib/src/maplabelitem.h \
 ../../3rdlib/GraphicsMapLib/src/mappieitem.h \
 ../../3rdlib/GraphicsMapLib/src/mapoperator.h    \
  ../../3rdlib/GraphicsMapLib/src/maplineitem.h \
  ../../3rdlib/GraphicsMapLib/src/mappolygonitem.h \
  ../../3rdlib/GraphicsMapLib/src/maprangeringitem.h \
   ../../3rdlib/GraphicsMapLib/src/maprouteitem.h \
   ../../3rdlib/GraphicsMapLib/src/maptrailitem.h \
   ../../3rdlib/GraphicsMapLib/src/maprectitem.h \
    ../../3rdlib/GraphicsMapLib/src/maptableitem.h \
    ../../3rdlib/GraphicsMapLib/src/mapscutcheonitem.h \
    ../../3rdlib/GraphicsMapLib/src/mapobjectitem.h \
    ../../3rdlib/GraphicsMapLib/src/graphicsmap.h \
    ../../3rdlib/GraphicsMapLib/src/GraphicsMapLib_global.h \
         ../../3rdlib/GraphicsMapLib/src/mappathitem.h \

