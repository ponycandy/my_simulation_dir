
TEMPLATE = lib
DEFINES += GRAYARAY

INCLUDEPATH += ../../../../build/config
INCLUDEPATH +=  ../../../../include
INCLUDEPATH +=  ../../../../
INCLUDEPATH +=  ../../../../3rdlib
DESTDIR =  ../../bin
CONFIG += c++17
QMAKE_CXXFLAGS += /arch:AVX
QMAKE_CXXFLAGS_DEBUG += /arch:AVX
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	GrayAray.cpp \
    greytheory.cpp

HEADERS += \
    GRAYARAY_global.h \
    GrayAray.h \
    greytheory.h
# 定义目标文件名
TARGET = GrayAray

# 定义要拷贝的文件
DESTDIR1 = ..\..\bin
DESTDIR2 = ..\..\..\..\build
# 定义拷贝命令
win32 {
    # Windows系统下的拷贝命令
    POST_LINKING_COMMAND = copy $${DESTDIR1}\\$${TARGET}.lib $${DESTDIR2}\\$${TARGET}.lib  &  copy $${DESTDIR1}\\$${TARGET}.dll $${DESTDIR2}\\$${TARGET}.dll
} else {
    # Unix/Linux系统下的拷贝命令
    POST_LINKING_COMMAND = cp ../../bin/$${TARGET}.lib $$DESTDIR2/$${TARGET}.lib  &  cp  ../../bin/$${TARGET}.dll $$DESTDIR2/$${TARGET}.dll
}

# 使用QMAKE_POST_LINK来执行拷贝命令
QMAKE_POST_LINK = $$POST_LINKING_COMMAND
