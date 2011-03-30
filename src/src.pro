QT       += gui

TARGET = qwin7utils
TEMPLATE = lib
CONFIG += staticlib

SOURCES += AppUserModel.cpp \
           JumpList.cpp \
    TaskbarButton.cpp \
    Taskbar.cpp \
    TaskbarToolbar.cpp \
    Utils.cpp \
    TaskbarTabs.cpp

HEADERS += AppUserModel.h \
           JumpList.h \
           win7_include.h \
    TaskbarButton.h \
    Taskbar.h \
    TaskbarToolbar.h \
    TBPrivateData.h \
    JLPrivateData.h \
    Utils.h \
    TaskbarTabs.h

#LIBS += libuser32 libole32 libshell32 libshlwapi
