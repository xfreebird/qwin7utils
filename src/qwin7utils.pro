#-------------------------------------------------
#
# Project created by QtCreator 2011-01-24T11:24:02
#
#-------------------------------------------------

QT       += gui

TARGET = qwin7utils
TEMPLATE = lib
CONFIG += staticlib

SOURCES += appusermodel.cpp \
           jumplist.cpp \
    taskbarbutton.cpp

HEADERS += appusermodel.h \
           jumplist.h \
           win7_include.h \
    taskbarbutton.h

#LIBS += libuser32 libole32 libshell32 libshlwapi
