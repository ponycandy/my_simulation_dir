#ipopt库

INCLUDEPATH+=../../3rdlib/Ipopt
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinmumps
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinmetis
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibcoinhsl
LIBS +=   -L../../3rdlib/Ipopt/ipoptlib/ -llibipopt


#MKL库
INCLUDEPATH += D:/oneAPI/mkl/2021.2.0/include
DEPENDPATH += D:/oneAPI/mkl/2021.2.0/include

LIBS += -LD:/Fronter_compiler_install/bin/mkl/2023.1.0/lib/intel64/ -lmkl_intel_lp64
LIBS += -LD:/Fronter_compiler_install/bin/mkl/2023.1.0/lib/intel64/ -lmkl_intel_thread
LIBS += -LD:/Fronter_compiler_install/bin/mkl/2023.1.0/lib/intel64/ -lmkl_core
LIBS += -LD:/Fronter_compiler_install/bin/compiler/2023.1.0/windows/compiler/lib/intel64_win/ -llibiomp5md

#下面这个是ifort所依赖的dll，不加这个不知道为什么会报错
LIBS += -LD:/Fronter_compiler_install/bin/mkl/2023.1.0/redist/intel64/ -lmkl_intel_thread


