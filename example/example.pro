#-------------------------------------------------
#
# Project created by QtCreator 2011-01-17T13:25:57
#
#-------------------------------------------------

QT       += core gui

TARGET = example
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
HEADERS += ../src/Taskbar.h \
    ../src/TaskbarButton.h \
    ../src/TaskbarToolbar.h \
    ../src/TaskbarTabs.h

FORMS    += mainwindow.ui

win32:RC_FILE  = example.rc

win32:debug {
    LIBS += -L$$PWD/../qwin7utils-build-desktop/debug
} else {
    LIBS += -L$$PWD/../qwin7utils-build-desktop/release
}

LIBS += libqwin7utils libuser32 libole32 libshell32 libshlwapi libcomctl32 libgdi32

RESOURCES += \
    icons.qrc
