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

#ifndef TASKBARTOOLBAR_H
#define TASKBARTOOLBAR_H

#include <QObject>

#ifdef Q_OS_WIN32
#include "taskbar.h"

/*
    void TaskbarButton::createCustomToolbar(QList<QPixmap>& images) {


        HIMAGELIST himl;
        if((himl = ImageList_Create( 20, //cx
                        20, //cy
                        ILC_COLOR32,//flags
                        4,//initial nb of images
                        0//nb of images that can be added
                        )))
        {
            QPixmap img   = images.at(0);//QPixmap(":/win7/prev");
            QPixmap img2  = images.at(1);//QPixmap(":/win7/pause");
            QPixmap img3  = images.at(2);//QPixmap(":/win7/play");
            QPixmap img4  = images.at(3);//QPixmap(":/win7/next");

            QBitmap mask  = img.createMaskFromColor(Qt::transparent);
            QBitmap mask2 = img2.createMaskFromColor(Qt::transparent);
            QBitmap mask3 = img3.createMaskFromColor(Qt::transparent);
            QBitmap mask4 = img4.createMaskFromColor(Qt::transparent);

            qDebug() << "thumbnails buttons";
            qDebug() << SUCCEEDED(ImageList_Add(himl, img.toWinHBITMAP(QPixmap::PremultipliedAlpha), mask.toWinHBITMAP()));
            qDebug() << SUCCEEDED(ImageList_Add(himl, img2.toWinHBITMAP(QPixmap::PremultipliedAlpha), mask2.toWinHBITMAP()));
            qDebug() << SUCCEEDED(ImageList_Add(himl, img3.toWinHBITMAP(QPixmap::PremultipliedAlpha), mask3.toWinHBITMAP()));
            qDebug() << SUCCEEDED(ImageList_Add(himl, img4.toWinHBITMAP(QPixmap::PremultipliedAlpha), mask4.toWinHBITMAP()));
        }

        // Define an array of two buttons. These buttons provide images through an
        // image list and also provide tooltips.
        DWORD dwMask = THB_BITMAP | THB_FLAGS;

        THUMBBUTTON thbButtons[3];
        thbButtons[0].dwMask = (THUMBBUTTONMASK)dwMask;
        thbButtons[0].iId = 30002;
        thbButtons[0].iBitmap = 0;
        thbButtons[0].dwFlags = (THUMBBUTTONFLAGS)(THBF_ENABLED);

        thbButtons[1].dwMask = (THUMBBUTTONMASK)dwMask;
        thbButtons[1].iId = 30003;
        thbButtons[1].iBitmap = 2;
        thbButtons[1].dwFlags = (THUMBBUTTONFLAGS)(THBF_DISABLED | THBF_NOBACKGROUND);

        thbButtons[2].dwMask = (THUMBBUTTONMASK)dwMask;
        thbButtons[2].iId = 30004;
        thbButtons[2].iBitmap = 3;
        thbButtons[2].dwFlags = (THUMBBUTTONFLAGS)(THBF_ENABLED);

        HRESULT hr = m_private->GetHandler()->ThumbBarSetImageList(m_widget_id, himl );
        qDebug() << hr;
        if(S_OK == hr){
            hr = m_private->GetHandler()->ThumbBarAddButtons(m_widget_id, 3, thbButtons);
            //hr = m_private->GetHandler()->ThumbBarUpdateButtons(m_widget_id, 3, thbButtons);
            qDebug() << hr;
        }
        qDebug() << "Toolbar end";


    }

 */
namespace QW7 {

    class TaskbarToolbar : public Taskbar
    {
        Q_OBJECT
    public:
        explicit TaskbarToolbar(QObject *parent = 0);


    };
}
#endif // Q_OS_WIN32

#endif // TASKBARTOOLBAR_H
