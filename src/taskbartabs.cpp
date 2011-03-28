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

#include "taskbartabs.h"

#ifdef Q_OS_WIN32
#include <QWidget>
#include <QDebug>
#include <QMainWindow>

#include "utils.h"
#include "win7_include.h"
#include "tbprivatedata.h"

namespace QW7 {

    TaskbarTabs* TaskbarTabs::m_instance = NULL;
    QCoreApplication::EventFilter TaskbarTabs::m_oldEventFilter = NULL;

    TaskbarTabs::TaskbarTabs(QWidget *parent) : Taskbar((QObject*)parent) {
    }

    TaskbarTabs* TaskbarTabs::GetInstance() {

        if (m_instance == NULL) {
            m_instance = new TaskbarTabs();
            m_oldEventFilter = qApp->setEventFilter(&TaskbarTabs::eventFilter);
        }

        return m_instance;
    }

    void TaskbarTabs::SetParentWidget(QWidget* widget) {
        m_parentWidget = widget;

        TaskbarTab* tab = new TaskbarTab();

        tab->m_widget = widget;
        tab->m_tab_widget = widget;

        m_tabs.append(tab);
    }

    void TaskbarTabs::AddTab(QWidget* widget, QString title) {
        TaskbarTab* tab = new TaskbarTab();

        tab->m_widget = widget;
        tab->m_tab_widget = new QWidget;
        tab->m_tab_widget->setWindowTitle(title);

        m_tabs.append(tab);
        EnableIconicPreview(tab->m_tab_widget, true);


        qDebug() << "AddWidget" << tab->m_tab_widget->winId();
        qDebug() << "RegisterTab " << m_private->GetHandler()->RegisterTab(tab->m_tab_widget->winId(), m_parentWidget->winId());
        qDebug() << "SetTabOrder " << m_private->GetHandler()->SetTabOrder(tab->m_tab_widget->winId(), NULL);
        qDebug() << "SetTabActive " << m_private->GetHandler()->SetTabActive(NULL, m_tabs.back()->m_tab_widget->winId(), 0);
    }

    void TaskbarTabs::RemoveTab(QWidget* widget) {
    }

    QWidget* TaskbarTabs::FindTabByWId(WId id) {
        bool found = false;

        TaskbarTab* tab;
        foreach(tab, m_tabs) {
            if (tab->m_tab_widget->winId() == id) {
                found = true;
                break;
            }
        }

        return found ? tab->m_widget : NULL;
    }

    void TaskbarTabs::TabAction(WId id, TABEVENT action) {
        QWidget* widget = FindTabByWId(id);

        if (widget != NULL) {
            switch (action) {
            case TAB_CLICK :
                emit OnTabClicked(widget);
                break;

            case TAB_CLOSE:
                emit OnTabClose(widget);
                break;

            case TAB_HOVER:
                emit OnTabHover(widget);
                break;
            }
        }
    }

    void TaskbarTabs::EnableIconicPreview(QWidget* widget, bool enable) {
        BOOL _enable = enable ? TRUE : FALSE;

        DwmSetWindowAttribute(
            widget->winId(),
            DWMWA_FORCE_ICONIC_REPRESENTATION,
            &_enable,
            sizeof(_enable));

        DwmSetWindowAttribute(
            widget->winId(),
            DWMWA_HAS_ICONIC_BITMAP,
            &_enable,
            sizeof(_enable));

    }

    void TaskbarTabs::SetIconicThumbnail(WId id, QSize size) {
        bool found = false;
        TaskbarTab* tab;

        foreach(tab, m_tabs) {
            if (tab->m_tab_widget->winId() == id) {
                found = true;
                break;
            }
        }

        if (!found) return;

        bool isParent = (tab->m_widget->winId() == m_parentWidget->winId());

        QPixmap thumbnail = QPixmap::grabWidget(tab->m_widget).scaled(size, Qt::KeepAspectRatio);
        HBITMAP hbitmap = thumbnail.toWinHBITMAP(isParent ? QPixmap::NoAlpha : QPixmap::Alpha);

        DwmSetIconicThumbnail(id, hbitmap, 0);

        if (hbitmap) DeleteObject(hbitmap);
    }

    void TaskbarTabs::SetIconicLivePreviewBitmap(WId id) {
        bool found = false;
        TaskbarTab* tab;

        foreach(tab, m_tabs) {
            if (tab->m_tab_widget->winId() == id) {
                found = true;
                break;
            }
        }

        if (!found) return;

        QPixmap thumbnail = QPixmap::grabWidget(m_parentWidget).scaled(m_parentWidget->size(), Qt::KeepAspectRatio);
        HBITMAP hbitmap = thumbnail.toWinHBITMAP();

        DwmSetIconicLivePreviewBitmap(id, hbitmap, 0, 0);

        if (hbitmap) DeleteObject(hbitmap);
    }

    bool TaskbarTabs::eventFilter(void *message_, long *result)
    {
        MSG *message = static_cast<MSG *>(message_);

        switch(message->message)
        {
        case WM_DWMSENDICONICTHUMBNAIL : {
                qDebug() << "Iconic " << message->hwnd;

                TaskbarTabs::GetInstance()->SetIconicThumbnail(message->hwnd, QSize(HIWORD(message->lParam), LOWORD(message->lParam)));
                return true;
            }
        case WM_DWMSENDICONICLIVEPREVIEWBITMAP : {
                qDebug() << "Live Start" << message->hwnd;

                TaskbarTabs::GetInstance()->TabAction(message->hwnd, TAB_HOVER);
                TaskbarTabs::GetInstance()->SetIconicLivePreviewBitmap(message->hwnd);
                return true;
            }
        case WM_ACTIVATE : {
                if (LOWORD(message->wParam) == WA_ACTIVE) {
                    qDebug() << "Activate " << message->hwnd << " " << TaskbarTabs::GetInstance()->m_parentWidget->winId();

                    TaskbarTabs::GetInstance()->TabAction(message->hwnd, TAB_CLICK);
                }
                return false;
            }
        case WM_CLOSE : {
                qDebug() << "Close " << message->hwnd;

                TaskbarTabs::GetInstance()->TabAction(message->hwnd, TAB_CLOSE);
                return false;
            }
        }

        if(TaskbarTabs::m_oldEventFilter)
            return TaskbarTabs::m_oldEventFilter(message_, result);
        else
            return false;
    }

    /*
    bool TaskbarTabs::winEvent(MSG* message, long* result) {

        switch (message->message)
        {
        case WM_DWMSENDICONICTHUMBNAIL: {
                qDebug() << "MIconic " << message->hwnd;

                QWidget* widget = NULL;
                foreach(widget, m_tabs) {
                    if (widget->winId() == message->hwnd) {
                        break;
                    }
                }

                if (!widget) return false;

                QPixmap thumbnail = QPixmap::grabWidget(widget).scaled(HIWORD(message->lParam), LOWORD(message->lParam), Qt::KeepAspectRatio);
                HBITMAP hbitmap = thumbnail.toWinHBITMAP();
                DwmSetIconicThumbnail(message->hwnd, hbitmap, 0);

                if (hbitmap) DeleteObject(hbitmap);


                return true;
            }
            break;

        case WM_DWMSENDICONICLIVEPREVIEWBITMAP: {
                qDebug() << "MLive " << message->hwnd;

                QWidget* widget = NULL;
                foreach(widget, m_tabs) {
                    if (widget->winId() == message->hwnd) {
                        break;
                    }
                }

                if (!widget) return false;

                QPixmap thumbnail = QPixmap::grabWidget(widget).scaled(HIWORD(message->lParam), LOWORD(message->lParam), Qt::KeepAspectRatio);
                HBITMAP hbitmap = thumbnail.toWinHBITMAP();

                POINT point;
                point.x = 0; point.y = 0;

                DwmSetIconicLivePreviewBitmap(message->hwnd, hbitmap, &point, 0);
                if (hbitmap) DeleteObject(hbitmap);


                return true;

            }
            break;

        case WM_ACTIVATE: {

                qDebug() << "WM_ACTIVATE " << message->hwnd;
                return true;
            }
            break;

        case WM_CLOSE: {
                qDebug() << "WM_CLOSE " << message->hwnd;
                return true;
            }
            break;

        }

        return qApp->winEventFilter(message, result);


    }
    */
}

#endif //Q_OS_WIN32
