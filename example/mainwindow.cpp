#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "../src/jumplist.h"
#include "../src/appusermodel.h"
#include "../src/taskbarbutton.h"

using namespace QW7;

QString g_app_id("WindowsAppQt");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    mTaskbar = new TaskbarButton(this);
    AppUserModel::SetCurrentProcessExplicitAppUserModelID(g_app_id);

#ifdef Q_OS_WIN32
    mtaskBarCreatedMessage = RegisterWindowMessage(L"TaskbarButtonCreated");
#endif //Q_OS_WIN32
}

MainWindow::~MainWindow()
{
    delete ui;
}

#ifdef Q_OS_WIN32
bool MainWindow::winEvent(MSG * message, long * result)
{
    if (message->message == mtaskBarCreatedMessage)
    {
        mTaskbar->Init();

        qDebug() << mTaskbar->SetState(STATE_PAUSED);
        qDebug() << mTaskbar->SetProgresValue(450, 1000);

        QList<JumpListItem> task_list;

        QString icons_source("C:\\windows\\explorer.exe");
        QString app_path = qApp->applicationFilePath();

        task_list.append(JumpListItem(app_path, "/tfoo 1", "Task 1", "Task 1 How To", icons_source, 2, "sd"));
        task_list.append(JumpListItem(app_path, "/tfoo 2", "Task 2", "Task 2 How To", icons_source, 10, "asd"));
        task_list.append(JumpListItem());
        task_list.append(JumpListItem(app_path, "/tfoo 3", "Task 3", "Task 3 How To", icons_source, 21, "das"));
        task_list.append(JumpListItem(app_path, "/tfoo 4", "Task 4", "Task 4 How To", icons_source, 20, "das"));

        QList<JumpListItem> other_list;
        other_list.append(JumpListItem(app_path, "/foo 1", "Email 1", "Something", icons_source, 15, "das"));
        other_list.append(JumpListItem(app_path, "/foo 2", "Email 2", "Something", icons_source, 15, "das"));
        other_list.append(JumpListItem(app_path, "/foo 3", "Email 3", "Something else", icons_source, 15, "das"));

        qDebug() << mJumpList.SetAppID(g_app_id);
        qDebug() << mJumpList.Begin();
        qDebug() << mJumpList.AddCategory("Starred (3)", other_list);
        qDebug() << mJumpList.AddUserTasks(task_list);
        qDebug() << mJumpList.Commit();
    }

    return false;
}

#endif //Q_OS_WIN32
