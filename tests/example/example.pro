#-------------------------------------------------
#
# Project created by QtCreator 2011-01-17T13:25:57
#
#-------------------------------------------------

QT       += core gui

TARGET = example
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    toolbardemo.cpp \
    progbarandicon.cpp \
    taskbartabsdemo.cpp

HEADERS  += mainwindow.h \
    toolbardemo.h \
    progbarandicon.h \
    taskbartabsdemo.h
HEADERS += ../../src/Taskbar.h \
    ../../src/TaskbarButton.h \
    ../../src/TaskbarToolbar.h \
    ../../src/TaskbarTabs.h

FORMS    += mainwindow.ui \
    toolbardemo.ui \
    progbarandicon.ui \
    taskbartabsdemo.ui

win32:RC_FILE  = example.rc

win32:debug {
    LIBS += -L$$PWD/../../../qwin7utils-build-desktop/src/debug
} else {
    LIBS += -L$$PWD/../../../qwin7utils-build-desktop/src/debug
}

LIBS += libqwin7utils libuser32 libole32 libshell32 libshlwapi libcomctl32 libgdi32

RESOURCES += \
    icons.qrc

#DEFINES += TRANSPARENT_WIDGET

unix {
     error( "Windows only code !!!" )
}
