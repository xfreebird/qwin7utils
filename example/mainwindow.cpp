#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPixmap>
#include <QList>
#include <QLineEdit>

#include "../src/utils.h"
#include "../src/jumplist.h"
#include "../src/appusermodel.h"
#include "../src/taskbarbutton.h"

/*
#define WM_DWMSENDICONICTHUMBNAIL         0x0323
#define WM_DWMSENDICONICLIVEPREVIEWBITMAP 0x0326


#include <windows.h>
*/
using namespace QW7;

QString g_app_id("WindowsQt");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    EnableBlurBehindWidget(this, true);
    ExtendFrameIntoClientArea(this);
    toolbarcanbeused = false;
    AppUserModel::SetCurrentProcessExplicitAppUserModelID(g_app_id);
    mTaskbar = new TaskbarButton(this);
    mToolbar = new TaskbarToolbar(this);

    QAction* action = new QAction(QIcon(":/prev.png"), "Prev", this);
    mToolbar->AddAction(action);

    action = new QAction(QIcon(":/play.png"), "Play", this);
    mToolbar->AddAction(action);
    special = action;

    action = new QAction(QIcon(":/next.png"), "Next", this);
    action->setData(QVariant("true"));
    mToolbar->AddAction(action);

    connect(mTaskbar, SIGNAL(isReady()), this, SLOT(on_pushButton_clicked()));

    connect(special, SIGNAL(triggered()), this, SLOT(actionpressed()));


    QIcon icon = QApplication::style()->standardIcon(QStyle::SP_VistaShield);
    ui->pushButton->setIcon(icon);

    mThumbnail = new TaskbarThumbnail(this);
    mThumbnail->SetThumbnail(QPixmap(":/logo.png"));

    mTabs = TaskbarTabs::GetInstance();
    mTabs->SetParentWidget(this);

    connect(mTabs, SIGNAL(OnTabClicked(QWidget*)), this, SLOT(tab_activated(QWidget*)));
    connect(mTabs, SIGNAL(OnTabHover(QWidget*)), this, SLOT(tab_activated(QWidget*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

#ifdef Q_OS_WIN32
bool MainWindow::winEvent(MSG * message, long * result)
{

    mTaskbar->winEvent(message, result);
    mToolbar->winEvent(message, result);
    mThumbnail->winEvent(message, result);
    //mTabs->winEvent(message, result);


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

    mThumbnail->EnableIconicPreview(true);
    mThumbnail->SetThumbnailTooltip("Hello World !!!");



    mTabs->AddTab(ui->tabWidget->widget(0), "Tab 1");
    mTabs->AddTab(ui->tabWidget->widget(1), "Tab 2");
    mTabs->AddTab(ui->tabWidget->widget(2), "Tab 3");
    mToolbar->Show();
}

void MainWindow::actionpressed() {
    static bool value = true;

    qDebug() << "Value = " << value;
    special->setIcon(value ? QIcon(":/pause.png") : QIcon(":/play.png"));
    special->setText(value ? "Pause" : "Play");
    value = !value;

    //mThumbnail->EnableIconicPreview(false);


}

void MainWindow::tab_activated(QWidget* widget) {

    this->activateWindow();

    for (int index = 0; index < 3; index++) {
        if (ui->tabWidget->widget(index) == widget) {
            ui->tabWidget->setCurrentIndex(index);
            break;
        }
    }
}
