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

#include "taskbar.h"

#ifdef Q_OS_WIN32
#include "tbprivatedata.h"
#include "win7_include.h"
#include <QDebug>

namespace QW7 {

    TBPrivateData* Taskbar::m_private = NULL;


    Taskbar::Taskbar(QObject* parent) : QObject(parent) {
    }


    bool Taskbar::winEvent(MSG* message, long* result) {
        static UINT taskBarCreatedId = WM_NULL;

        if (taskBarCreatedId == WM_NULL) {
            taskBarCreatedId = RegisterWindowMessage(L"TaskbarButtonCreated");
        }

        if (message->message == taskBarCreatedId) {
            if (!m_private) {
                m_private = new TBPrivateData();

                if (m_private) {
                    emit isReady();
                }
            }
        } else switch (message->message){
                default:
                    return false;
        }

        return false;
    }

    Taskbar::~Taskbar() {
        if (m_private) {
            delete m_private;
            m_private = NULL;
        }
    }
}

#endif //Q_OS_WIN32
