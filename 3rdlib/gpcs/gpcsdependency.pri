


INCLUDEPATH += ../../3rdlib/gpcs/include
LIBS +=   -L../../3rdlib/gpcs/lib/ -lgpcslib
INCLUDEPATH += $(BOOST_INCLUDEDIR)
LIBS += -L$(BOOST_LIBRARYDIR) -llibboost_thread-vc143-mt-gd-x64-1_83
