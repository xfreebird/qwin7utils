#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <initguid.h>
#include <objidl.h>
#include "../src/jumplist.h"
#include "../src/appusermodel.h"
#include "../src/taskbarbutton.h"

#include <QTimer>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

#ifdef Q_OS_WIN32
protected:
    bool winEvent(MSG * message, long * result);
#endif //Q_OS_WIN32

private:
    Ui::MainWindow *ui;
    QW7::JumpList mJumpList;
    QW7::TaskbarButton* mTaskbar;

#ifdef Q_OS_WIN32
    UINT mtaskBarCreatedMessage;
#endif //Q_OS_WIN32
};

#endif // MAINWINDOW_H
