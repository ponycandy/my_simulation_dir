
#LIBS *= -LD:/Fronter_compiler_install/bin/compiler/latest/windows/compiler/lib/intel64_win
#win32 {
#    SHARED_LIB_FILES = $$files($$PWD/MYLIBS/*.lib)
#    for(FILE, SHARED_LIB_FILES) {
#        BASENAME = $$basename(FILE)
#        LIBS += -l$$replace(BASENAME,.lib,)
#    }
#}
#unix {
#    SHARED_LIB_FILES = $$files($$PWD/MYLIBS/*.so)
#    for(FILE, SHARED_LIB_FILES) {
#        BASENAME = $$basename(FILE)
#        LIBS += -l$$replace(BASENAME,.so,)
#    }
#}

#LIBS *= -LD:/Fronter_compiler_install/bin/mkl/2023.1.0/lib/intel64
#win32 {
#    SHARED_LIB_FILES = $$files($$PWD/MYLIBS/*.lib)
#    for(FILE, SHARED_LIB_FILES) {
#        BASENAME = $$basename(FILE)
#        LIBS += -l$$replace(BASENAME,.lib,)
#    }
#}
#unix {
#    SHARED_LIB_FILES = $$files($$PWD/MYLIBS/*.so)
#    for(FILE, SHARED_LIB_FILES) {
#        BASENAME = $$basename(FILE)
#        LIBS += -l$$replace(BASENAME,.so,)
#    }
#}

#一下是第二种添加MKL库的方式
INCLUDEPATH += D:/oneAPI/mkl/2021.2.0/include
DEPENDPATH += D:/oneAPI/mkl/2021.2.0/include

LIBS += -LD:/Fronter_compiler_install/bin/mkl/2023.1.0/lib/intel64/ -lmkl_intel_lp64
LIBS += -LD:/Fronter_compiler_install/bin/mkl/2023.1.0/lib/intel64/ -lmkl_intel_thread
LIBS += -LD:/Fronter_compiler_install/bin/mkl/2023.1.0/lib/intel64/ -lmkl_core
LIBS += -LD:/Fronter_compiler_install/bin/compiler/2023.1.0/windows/compiler/lib/intel64_win/ -llibiomp5md
