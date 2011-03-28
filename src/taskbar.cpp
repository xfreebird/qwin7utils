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
#include <QMutex>
#include <QMutexLocker>
#include "tbprivatedata.h"
#include "win7_include.h"

namespace QW7 {

    QMutex Taskbar::m_mutex;
    int Taskbar::m_instanceCounter = 0;
    TBPrivateData* Taskbar::m_private = NULL;


    Taskbar::Taskbar(QObject* parent) : QObject(parent) {
        QMutexLocker locker(&m_mutex);

        m_instanceCounter++;
        m_taskBarCreatedId = WM_NULL;
    }


    bool Taskbar::winEvent(MSG* message, long* result) {
        if (m_taskBarCreatedId == WM_NULL) {
            m_taskBarCreatedId = RegisterWindowMessage(L"TaskbarButtonCreated");
        }

        if (message->message == m_taskBarCreatedId) {
            QMutexLocker locker(&m_mutex);

            if (!m_private) {
                m_private = new TBPrivateData();

                if (m_private) {
                    emit isReady();
                    return true;
                }
            }

        }

        return qApp->winEventFilter(message, result);
    }

    Taskbar::~Taskbar() {
        QMutexLocker locker(&m_mutex);

        m_instanceCounter--;

        if (m_instanceCounter == 0) {
            if (m_private) {
                delete m_private;
                m_private = NULL;
            }
        }
    }
}

#endif //Q_OS_WIN32
