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

#include "taskbartoolbar.h"

#ifdef Q_OS_WIN32
#include <QBitmap>
#include <QPixmap>
#include <QString>

#include "win7_include.h"
#include "tbprivatedata.h"

#define IDTB_FIRST 3000

namespace QW7 {

    TaskbarToolbar::TaskbarToolbar(QObject *parent) :
            Taskbar(parent)
    {
        m_initialized = false;
        SetWindow(parent);
    }

    void TaskbarToolbar::SetWindow(QObject* window) {
        m_widget_id = dynamic_cast<QWidget*>(window)->winId();
    }


    void TaskbarToolbar::AddAction(QAction* action) {
        if (m_initialized) return;

        m_actions.append(action);

        connect(action, SIGNAL(changed()), this, SLOT(OnActionChanged()));
    }

    void TaskbarToolbar::AddActions(QList<QAction*>& actions) {
        if (m_initialized) return;

        RemoveActions();

        m_actions.append(actions);

        QAction* action;
        foreach(action, m_actions) {
            connect(action, SIGNAL(changed()), this, SLOT(OnActionChanged()));
        }
    }

    void TaskbarToolbar::RemoveActions() {
        QAction* action;

        foreach(action, m_actions) {
            disconnect(action, SIGNAL(changed()), this, SLOT(OnActionChanged()));
        }

        m_actions.clear();
    }

    void TaskbarToolbar::OnActionChanged() {
        Show();
    }

    void TaskbarToolbar::Show() {
        HIMAGELIST himl = ImageList_Create(20, 20, ILC_COLOR32, m_actions.size(), 0);

        THUMBBUTTON* thbButtons = new THUMBBUTTON[m_actions.size()];

        if (!himl) return;
        if (!thbButtons) return;

        int index = 0;
        QAction* action;

        foreach(action, m_actions) {
            QPixmap img = action->icon().pixmap(20);
            QBitmap mask  = img.createMaskFromColor(Qt::transparent);

            ImageList_Add(himl, img.toWinHBITMAP(QPixmap::PremultipliedAlpha), mask.toWinHBITMAP());

            wcscpy(thbButtons[index].szTip, action->text().toStdWString().c_str());

            thbButtons[index].iId = IDTB_FIRST + index;
            thbButtons[index].iBitmap = index;
            thbButtons[index].dwMask = (THUMBBUTTONMASK)(THB_BITMAP | THB_FLAGS | THB_TOOLTIP);
            thbButtons[index].dwFlags = (THUMBBUTTONFLAGS)(action->isEnabled() ? THBF_ENABLED : THBF_DISABLED);

            if (!action->isVisible()) thbButtons[index].dwFlags = (THUMBBUTTONFLAGS)(thbButtons[index].dwFlags | THBF_HIDDEN);
            if (action->data().toBool()) thbButtons[index].dwFlags = (THUMBBUTTONFLAGS)(thbButtons[index].dwFlags | THBF_DISMISSONCLICK);

            ++index;
        }

        HRESULT hr = m_private->GetHandler()->ThumbBarSetImageList(m_widget_id, himl);

        if (S_OK == hr) {
            if (!m_initialized) {
                m_private->GetHandler()->ThumbBarAddButtons(m_widget_id, m_actions.size(), thbButtons);
            } else {
                m_private->GetHandler()->ThumbBarUpdateButtons(m_widget_id, m_actions.size(), thbButtons);
            }
        }

        m_initialized = true;

        delete[] thbButtons;
        ImageList_Destroy(himl);
    }

    bool TaskbarToolbar::winEvent(MSG* message, long* result) {

        switch (message->message)
        {
        case WM_COMMAND:
            {
                int buttonId = LOWORD(message->wParam) - IDTB_FIRST;

                if ((buttonId >= 0) && (buttonId < m_actions.size())) {
                    QAction* action = m_actions.at(buttonId);

                    if (action) action->trigger();
                }


                break;
            }

        default:
            return false;
        }

        return Taskbar::winEvent(message, result);
    }


    TaskbarToolbar::~TaskbarToolbar() {
        RemoveActions();
    }


}

#endif //Q_OS_WIN32
