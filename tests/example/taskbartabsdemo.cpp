/***************************************************************************
 *   Copyright (C) 2011 by Nicolae Ghimbovschi                             *
 *     nicolae.ghimbovschi@gmail.com                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 3 of the License.               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "taskbartabsdemo.h"
#include "ui_taskbartabsdemo.h"

#include "../../src/Utils.h"
#include "../../src/Taskbar.h"

#include <QDebug>

using namespace QW7;
TaskbarTabsDemo::TaskbarTabsDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TaskbarTabsDemo)
{
    ui->setupUi(this);

#ifdef TRANSPARENT_WIDGET
    //set window transparent
    EnableBlurBehindWidget(this, true);
    ExtendFrameIntoClientArea(this);
#endif //TRANSPARENT_WIDGET

    mTaskbarTabs = TaskbarTabs::GetInstance();
    mTaskbarTabs->SetParentWidget(this);

    connect(mTaskbarTabs, SIGNAL(OnTabClicked(QWidget*)), this, SLOT(OnTabActivate(QWidget*)));
    connect(mTaskbarTabs, SIGNAL(OnTabHover(QWidget*)), this, SLOT(OnTabActivate(QWidget*)));
    connect(mTaskbarTabs, SIGNAL(OnTabClose(QWidget*)), this, SLOT(OnTabRemove(QWidget*)));

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(OnTabActivate(int)));
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(OnTabRemove(int)));

    connect(ui->actionAdd_Tab, SIGNAL(triggered()), this, SLOT(OnTabAdd()));

    connect(Taskbar::GetInstance(), SIGNAL(isReady()), this, SLOT(OnTaskbarReady()));
}

bool TaskbarTabsDemo::winEvent(MSG * message, long * result) {
    //init taskbar
    Taskbar::GetInstance()->winEvent(message, result);

    return false;
}

void TaskbarTabsDemo::OnTaskbarReady() {
    mTaskbarTabs->AddTab(ui->tabWidget->widget(0), QString("Tab 1"), QIcon(":/home.png"));
    mTaskbarTabs->AddTab(ui->tabWidget->widget(1), QString("Tab 2"), QIcon(":/flag.png"));
    mTaskbarTabs->AddTab(ui->tabWidget->widget(2), QString("Custom thumbnail"), QIcon(":/feed.png"), QPixmap(":/logo.png"));
    mTaskbarTabs->SetActiveTab(ui->tabWidget->widget(0));
}

void TaskbarTabsDemo::OnTabActivate(QWidget* widget) {
    activateWindow();

    for (int index = 0; index < ui->tabWidget->count(); index++) {
        if (ui->tabWidget->widget(index) == widget) {
            ui->tabWidget->setCurrentIndex(index);
            break;
        }
    }

}

void TaskbarTabsDemo::OnTabRemove(QWidget* widget) {
    for (int index = 0; index < ui->tabWidget->count(); index++) {
        if (widget == ui->tabWidget->widget(index)) {
            OnTabRemove(index);
            break;
        }
    }
}

void TaskbarTabsDemo::OnTabActivate(int index) {
    QWidget* widget = ui->tabWidget->widget(index);
    if (widget) mTaskbarTabs->SetActiveTab(widget);
}

void TaskbarTabsDemo::OnTabRemove(int index) {
    QWidget* widget = ui->tabWidget->widget(index);
    ui->tabWidget->removeTab(index);
    mTaskbarTabs->RemoveTab(widget);
}

void TaskbarTabsDemo::OnTabAdd() {
    QWidget* widget = new QWidget();
    ui->tabWidget->addTab(widget, "New Tab");
    mTaskbarTabs->AddTab(widget, "New Tab");
}


TaskbarTabsDemo::~TaskbarTabsDemo()
{
    delete ui;
}
