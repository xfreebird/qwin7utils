#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QIcon>
#include <QPixmap>

#include "../../src/Utils.h"
#include "../../src/AppUserModel.h"

using namespace QW7;

QString g_app_id("WindowsQt");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

#ifdef TRANSPARENT_WIDGET
    //set window transparent
    EnableBlurBehindWidget(this, true);
    ExtendFrameIntoClientArea(this);
#endif //TRANSPARENT_WIDGET

    AppUserModel::SetCurrentProcessExplicitAppUserModelID(g_app_id);

    QIcon icon = QApplication::style()->standardIcon(QStyle::SP_VistaShield);
    ui->pushButton->setIcon(icon);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QList<JumpListItem> task_list;

    QString icons_source("C:\\windows\\explorer.exe");
    QString app_path = qApp->applicationFilePath();
    QString app_dir_path = qApp->applicationDirPath();

    task_list.append(JumpListItem(app_path, "/arg 1", "Task 1", "Task 1 How To", icons_source, 2, app_dir_path));
    task_list.append(JumpListItem(app_path, "/arg 2", "Task 2", "Task 2 How To", icons_source, 10, app_dir_path));
    task_list.append(JumpListItem());
    task_list.append(JumpListItem(app_path, "/arg 3", "Task 3", "Task 3 How To", icons_source, 21, app_dir_path));

    QList<JumpListItem> other_list;
    //other_list.append(JumpListItem("C:\\file.mmm"));
    other_list.append(JumpListItem(app_path, "/foo 1", "Email 1", "Something", icons_source, 15, app_dir_path));
    other_list.append(JumpListItem(app_path, "/foo 3", "Email 2", "Something else", icons_source, 15, app_dir_path));

    mJumpList.SetAppID(g_app_id);
    mJumpList.Begin();
    mJumpList.AddCategory("Unread (2)", other_list);
    //mJumpList.AddFrequentCategory();
    //mJumpList.AddRecentCategory();
    mJumpList.AddUserTasks(task_list);
    mJumpList.Commit();

    ui->pushButton->setDisabled(true);
}

