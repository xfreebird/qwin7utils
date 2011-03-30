#include <QtGui/QApplication>

#include "mainwindow.h"
#include "toolbardemo.h"
#include "progbarandicon.h"
#include "taskbartabsdemo.h"

#include "../../src/Taskbar.h"
#include "../../src/TaskbarTabs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow jumpListDemo;
    jumpListDemo.show();

    ToolbarDemo toolbarDemo;
    toolbarDemo.show();

    ProgBarAndIcon progbarAndIcon;
    progbarAndIcon.show();

    TaskbarTabsDemo taskbarTabsDemo;
    taskbarTabsDemo.show();

    jumpListDemo.move(QPoint(20, 20));
    toolbarDemo.move(QPoint(20, 300));
    progbarAndIcon.move(QPoint(20, 120));
    taskbarTabsDemo.move(QPoint(500, 20));

    int result = a.exec();

    QW7::TaskbarTabs::ReleaseInstance();
    QW7::Taskbar::ReleaseInstance();

    return result;
}
