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

#include "toolbardemo.h"
#include "ui_toolbardemo.h"

#include "../../src/Utils.h"
#include "../../src/Taskbar.h"

#include <QDebug>

using namespace QW7;

ToolbarDemo::ToolbarDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToolbarDemo)
{
    mImageIndex = 1;
    ui->setupUi(this);

    setFixedSize(size());

    //set window transparent
    EnableBlurBehindWidget(this, true);
    ExtendFrameIntoClientArea(this);

    mToolbar = new TaskbarToolbar(this);

    mPrevAction = new QAction(QIcon(":/prev.png"), "Prev", this);
    mToolbar->AddAction(mPrevAction);

    mPlayPauseAction = new QAction(QIcon(":/play.png"), "Play", this);
    mToolbar->AddAction(mPlayPauseAction);

    mNextAction = new QAction(QIcon(":/next.png"), "Next", this);
    mToolbar->AddAction(mNextAction);

    connect(mPrevAction, SIGNAL(triggered()), this, SLOT(OnPrevAction()));
    connect(mPlayPauseAction, SIGNAL(triggered()), this, SLOT(OnPlayPauseAction()));
    connect(mNextAction, SIGNAL(triggered()), this, SLOT(OnNextAction()));

    connect(Taskbar::GetInstance(), SIGNAL(isReady()), this, SLOT(OnTaskbarReady()));
}

bool ToolbarDemo::winEvent(MSG * message, long * result) {
    //init taskbar
    Taskbar::GetInstance()->winEvent(message, result);
    mToolbar->winEvent(message, result);

    return false;
}

void ToolbarDemo::SetImage() {
    if (mImageIndex == 0) {
        mImageIndex++;
        ui->label->setPixmap(QPixmap(":/cover.png"));
    } else {
        mImageIndex--;
        ui->label->setPixmap(QPixmap(":/bethoven.png"));
    }
}

void ToolbarDemo::OnTaskbarReady() {
    mToolbar->SetThumbnailTooltip("Window thumbnail tooltip.");
    mToolbar->SetThumbnailClip(ui->label->frameGeometry());
    mToolbar->Show();
}

void ToolbarDemo::OnPrevAction() {
    SetImage();
    ui->labelPlayStats->setText("Prev button pressed");
}

void ToolbarDemo::OnPlayPauseAction() {
    if (mPlayPauseAction->text() == "Play") {
        ui->labelPlayStats->setText("Play button pressed");
        mPlayPauseAction->setText("Pause");
        mPlayPauseAction->setIcon(QIcon(":/pause.png"));
    } else {
        ui->labelPlayStats->setText("Pause button pressed");
        mPlayPauseAction->setText("Play");
        mPlayPauseAction->setIcon(QIcon(":/play.png"));
    }
}

void ToolbarDemo::OnNextAction() {
    SetImage();
    ui->labelPlayStats->setText("Next button pressed");
}

ToolbarDemo::~ToolbarDemo()
{
    delete ui;
}
