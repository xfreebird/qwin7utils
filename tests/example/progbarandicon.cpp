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

#include "progbarandicon.h"
#include "ui_progbarandicon.h"

#include "../../src/Utils.h"
#include "../../src/Taskbar.h"

#include <QDebug>

using namespace QW7;

#define MIN_VALUE 0
#define MAX_VALUE 100

ProgBarAndIcon::ProgBarAndIcon(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgBarAndIcon)
{
    ui->setupUi(this);

#ifdef TRANSPARENT_WIDGET
    //set window transparent
    EnableBlurBehindWidget(this, true);
    ExtendFrameIntoClientArea(this);
#endif //TRANSPARENT_WIDGET

    mProgressValue = MIN_VALUE;
    mTaskbarButton = new TaskbarButton(this);

    ui->progressBar->setMinimum(MIN_VALUE);
    ui->progressBar->setMaximum(MAX_VALUE);

    connect(&mTimer, SIGNAL(timeout()), this, SLOT(OnUpdateProgressValue()));
    connect(Taskbar::GetInstance(), SIGNAL(isReady()), this, SLOT(OnTaskbarReady()));
}

bool ProgBarAndIcon::winEvent(MSG * message, long * result) {
    //init taskbar
    Taskbar::GetInstance()->winEvent(message, result);

    return false;
}

void ProgBarAndIcon::OnTaskbarReady() {
    connect(ui->cbProgressType, SIGNAL(currentIndexChanged(int)), this, SLOT(OnProgressTypeChanged()));
    connect(ui->cbOverlayIcon, SIGNAL(currentIndexChanged(int)), this, SLOT(OnOverlayIconChanged()));
}

void ProgBarAndIcon::OnProgressTypeChanged() {
    ui->progressBar->setMaximum(MAX_VALUE);

    switch (ui->cbProgressType->currentIndex()) {
    case 0: mTaskbarButton->SetState(STATE_NOPROGRESS); mTimer.stop(); mProgressValue = 0;
            ui->progressBar->setValue(0);
            break;

    case 1: mTaskbarButton->SetState(STATE_INDETERMINATE);
            ui->progressBar->setValue(1);
            ui->progressBar->setMaximum(0);
            mTimer.stop();
            break;

    case 2: mTaskbarButton->SetState(STATE_NORMAL); mProgressValue = 0; mTimer.start(100);
            break;

    case 3: mTaskbarButton->SetState(STATE_ERROR); mTimer.stop();
            break;

    case 4: mTaskbarButton->SetState(STATE_PAUSED); mTimer.stop();
            break;
    }
}

void ProgBarAndIcon::OnOverlayIconChanged() {
    mTaskbarButton->SetOverlayIcon(ui->cbOverlayIcon->itemIcon(ui->cbOverlayIcon->currentIndex()), "");
}

void ProgBarAndIcon::OnUpdateProgressValue() {
    mProgressValue++;

    if (mProgressValue > MAX_VALUE) mProgressValue = 0;

    ui->progressBar->setValue(mProgressValue);
    mTaskbarButton->SetProgresValue(mProgressValue, MAX_VALUE);
}

ProgBarAndIcon::~ProgBarAndIcon()
{
    mTimer.stop();
    delete ui;
}
