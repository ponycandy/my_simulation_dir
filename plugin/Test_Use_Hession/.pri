INCLUDEPATH += ../../3rdlib/ifopt/ifopt_lib
INCLUDEPATH += ../../3rdlib
#LIBS += -L../../3rdlib/ifopt/ifopt_lib/ -lifopt_core
#LIBS += -L../../3rdlib/ifopt/ifopt_lib/ -lifopt_ipopt

SOURCES += \
    ../../3rdlib/ifopt/ifopt_core/src/composite.cc \
    ../../3rdlib/ifopt/ifopt_core/src/leaves.cc \
     ../../3rdlib/ifopt/ifopt_core/src/problem.cc \





HEADERS += \
    ../../3rdlib/ifopt/ifopt_core/include/ifopt/bounds.h \
    ../../3rdlib/ifopt/ifopt_core/include/ifopt/composite.h \
    ../../3rdlib/ifopt/ifopt_core/include/ifopt/constraint_set.h \
    ../../3rdlib/ifopt/ifopt_core/include/ifopt/cost_term.h \
    ../../3rdlib/ifopt/ifopt_core/include/ifopt/problem.h \
    ../../3rdlib/ifopt/ifopt_core/include/ifopt/solver.h \
    ../../3rdlib/ifopt/ifopt_core/include/ifopt/variable_set.h \
