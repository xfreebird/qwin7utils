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

#include <QBitmap>
#include <QPixmap>
#include <QPainter>

#include "taskbarbutton.h"

#ifdef Q_OS_WIN32
#include "win7_include.h"
#include "tbprivatedata.h"
#include <QAction>
namespace QW7 {

    TaskbarButton::TaskbarButton(QObject* parent) : Taskbar(parent) {
        SetWindow(parent);
    }

    void TaskbarButton::SetWindow(QObject* window) {
        m_widget_id = dynamic_cast<QWidget*>(window)->winId();
    }

    long TaskbarButton::SetOverlayIcon(const QIcon& icon, QString description) {
        if (m_private) {
            HICON overlay_icon = icon.isNull() ? NULL : icon.pixmap(48).toWinHICON();
            long result = m_private->GetHandler()->SetOverlayIcon(m_widget_id, overlay_icon, description.toStdWString().c_str());

            if (overlay_icon) {
                DestroyIcon(overlay_icon);
                return result;
            }
        }

        return -1;
    }

    long TaskbarButton::SetState(ProgressBarState state) {
        if (m_private) {
            return m_private->GetHandler()->SetProgressState(m_widget_id, (TBPFLAG)state);
        }

        return -1;
    }

    long TaskbarButton::SetProgresValue(unsigned long long done, unsigned long long total) {
        if (m_private) {
            return m_private->GetHandler()->SetProgressValue(m_widget_id, done, total);
        }

        return -1;
    }

}

#endif //Q_OS_WIN32
