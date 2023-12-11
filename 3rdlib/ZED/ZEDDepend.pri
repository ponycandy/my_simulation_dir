
include (../../3rdlib/Opencv/OpencvDepend.pri)

INCLUDEPATH += "C:/Program Files (x86)/ZED SDK/include"
INCLUDEPATH += "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.7/include"
#INCLUDEPATH += C:/Program Files (x86)/ZED SDK/include
#
#INCLUDEPATH += D:/oneAPI/MKL/mkl/2023.1.0/include
#LIBS += -LC:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.7/lib/x64 -lcudart
#LIBS += -LC:/Program Files (x86)/ZED SDK/lib -lsl_zed64

LIBS += -L"C:/Program Files (x86)/ZED SDK/lib" -lsl_zed64
LIBS += -L"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.7/lib/x64" -lcudart
