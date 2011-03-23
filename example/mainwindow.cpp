#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPixmap>
#include <QList>
#include <QPainter>
#include <QPaintEngine>

#include "../src/jumplist.h"
#include "../src/appusermodel.h"
#include "../src/taskbarbutton.h"

using namespace QW7;

QString g_app_id("WindowsQt");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    AppUserModel::SetCurrentProcessExplicitAppUserModelID(g_app_id);
    mTaskbar = new TaskbarButton(this);
    connect(mTaskbar, SIGNAL(isReady()), this, SLOT(on_pushButton_clicked()));

    QIcon icon = QApplication::style()->standardIcon(QStyle::SP_VistaShield);
    ui->pushButton->setIcon(icon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#ifdef Q_OS_WIN32
bool MainWindow::winEvent(MSG * message, long * result)
{
    mTaskbar->winEvent(message, result);

    return false;
}

#endif //Q_OS_WIN32

void MainWindow::on_pushButton_clicked()
{

    QList<JumpListItem> task_list;

    QString icons_source("C:\\windows\\explorer.exe");
    QString app_path = qApp->applicationFilePath();

    task_list.append(JumpListItem(app_path, "/tfoo 1", "Task 1", "Task 1 How To", icons_source, 2, "sd"));
    task_list.append(JumpListItem(app_path, "/tfoo 2", "Task 2", "Task 2 How To", icons_source, 10, "asd"));
    task_list.append(JumpListItem());
    task_list.append(JumpListItem(app_path, "/tfoo 3", "Task 3", "Task 3 How To", icons_source, 21, "das"));

    QList<JumpListItem> other_list;
    other_list.append(JumpListItem("C:\\file.mmm"));
    other_list.append(JumpListItem(app_path, "/foo 1", "Email 1", "Something", icons_source, 15, "das"));
    other_list.append(JumpListItem(app_path, "/foo 3", "Email 3", "Something else", icons_source, 15, "das"));

    qDebug() << mJumpList.SetAppID(g_app_id);
    qDebug() << mJumpList.Begin();
    qDebug() << mJumpList.AddCategory("Starred (2)", other_list);
    //qDebug() << mJumpList.AddFrequentCategory();
    //qDebug() << mJumpList.AddRecentCategory();
    qDebug() << mJumpList.AddUserTasks(task_list);
    qDebug() << mJumpList.Commit();

    mTaskbar->SetState(STATE_PAUSED);
    mTaskbar->SetProgresValue(300, 900);

}
