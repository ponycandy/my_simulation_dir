#ipopt库

INCLUDEPATH+=../../3rdlib/Ipopt
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinmumps
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinmetis
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinhsl
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibipopt


#MKL库
INCLUDEPATH += D:/oneAPI/MKL/mkl/2023.1.0/include
DEPENDPATH += D:/oneAPI/MKL/mkl/2023.1.0/include

LIBS += -LD:/oneAPI/MKL/mkl/2023.1.0/lib/intel64 -lmkl_intel_lp64
LIBS += -LD:/oneAPI/MKL/mkl/2023.1.0/lib/intel64 -lmkl_intel_thread
LIBS += -LD:/oneAPI/MKL/mkl/2023.1.0/lib/intel64 -lmkl_core
LIBS += -LD:/oneAPI/MKL/compiler/2023.1.0/windows/compiler/lib/intel64_win/ -llibiomp5md

#下面这个是ifort所依赖的dll，不加这个不知道为什么会报错
LIBS += -LD:/oneAPI/MKL/mkl/2023.1.0/lib/intel64/ -lmkl_intel_thread


#LIBS *= -LD:/oneAPI/MKL/mkl/2023.1.0/lib/intel64
#win32 {
#  STATIC_LIB_FILES = $$files(D:/oneAPI/MKL/mkl/2023.1.0/lib/intel64/*.lib)
#  for (FILE, STATIC_LIB_FILES) {
#    BASENAME = $$basename(FILE)
#    LIBS += -l$$replace(BASENAME, .lib, )
#  }
#}
#unix {
#  STATIC_LIB_FILES = $$files(D:/oneAPI/MKL/mkl/2023.1.0/lib/intel64/*.a)
#  for (FILE, STATIC_LIB_FILES) {
#    BASENAME = $$basename(FILE)
#    LIBS += -l$$replace(BASENAME, .a, )
#  }
#}

#LIBS *= -LD:/oneAPI/MKL/compiler/2023.1.0/windows/compiler/lib/intel64_win
#win32 {
#  STATIC_LIB_FILES = $$files(D:/oneAPI/MKL/compiler/2023.1.0/windows/compiler/lib/intel64_win/*.lib)
#  for (FILE, STATIC_LIB_FILES) {
#    BASENAME = $$basename(FILE)
#    LIBS += -l$$replace(BASENAME, .lib, )
#  }
#}
#unix {
#  STATIC_LIB_FILES = $$files(D:/oneAPI/MKL/compiler/2023.1.0/windows/compiler/lib/intel64_win/*.a)
#  for (FILE, STATIC_LIB_FILES) {
#    BASENAME = $$basename(FILE)
#    LIBS += -l$$replace(BASENAME, .a, )
#  }
#}
