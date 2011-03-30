#include <QtGui/QApplication>
#include "mainwindow.h"
#include "toolbardemo.h"
#include "progbarandicon.h"
#include "taskbartabsdemo.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    ToolbarDemo toolbarDemo;
    toolbarDemo.show();

    ProgBarAndIcon progbarAndIcon;
    progbarAndIcon.show();

    TaskbarTabsDemo taskbarTabsDemo;
    taskbarTabsDemo.show();

    return a.exec();
}
