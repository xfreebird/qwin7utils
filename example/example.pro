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

FORMS    += mainwindow.ui

win32:RC_FILE  = example.rc

win32:debug {
    LIBS += -L$$PWD/../libin/debug
} else {
    LIBS += -L$$PWD/../libin/release
}

LIBS += libqwin7utils libuser32 libole32 libshell32 libshlwapi

