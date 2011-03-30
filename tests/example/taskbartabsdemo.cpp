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

    mTaskbarTabs = TaskbarTabs::GetInstance();
    mTaskbarTabs->SetParentWidget(this);

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

TaskbarTabsDemo::~TaskbarTabsDemo()
{
    delete ui;
}
