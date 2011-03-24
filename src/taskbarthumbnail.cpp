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

#include "taskbarthumbnail.h"

#ifdef Q_OS_WIN32
#include <QWidget>

#include "win7_include.h"
#include "tbprivatedata.h"

namespace QW7 {

    void DwmSetIconicThumbnail(HWND hwnd, HBITMAP hbmp, DWORD dwSITFlags) {
        HMODULE shell;

        shell = LoadLibrary(L"dwmapi.dll");
        if (shell) {
            t_DwmSetIconicThumbnail set_iconic_thumbnail = reinterpret_cast<t_DwmSetIconicThumbnail>(GetProcAddress (shell, "DwmSetIconicThumbnail"));
            set_iconic_thumbnail(hwnd, hbmp, dwSITFlags);

            FreeLibrary (shell);
        }
    }

    void DwmSetWindowAttribute(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute) {
        HMODULE shell;

        shell = LoadLibrary(L"dwmapi.dll");
        if (shell) {
            t_DwmSetWindowAttribute set_window_attribute = reinterpret_cast<t_DwmSetWindowAttribute>(GetProcAddress (shell, "DwmSetWindowAttribute"));
            set_window_attribute(hwnd, dwAttribute, pvAttribute, cbAttribute);

            FreeLibrary (shell);
        }
    }

    void DwmSetIconicLivePreviewBitmap(HWND hwnd, HBITMAP hbmp, POINT *pptClient, DWORD dwSITFlags) {
        HMODULE shell;

        shell = LoadLibrary(L"dwmapi.dll");
        if (shell) {
            t_DwmSetIconicLivePreviewBitmap set_live_preview = reinterpret_cast<t_DwmSetIconicLivePreviewBitmap>(GetProcAddress (shell, "DwmSetIconicLivePreviewBitmap"));
            set_live_preview(hwnd, hbmp, pptClient, dwSITFlags);

            FreeLibrary (shell);
        }
    }

    TaskbarThumbnail::TaskbarThumbnail(QObject *parent) : QObject(parent) {//:  Taskbar(parent) {
        SetWindow(parent);
    }

    void TaskbarThumbnail::SetWindow(QObject* window) {
        m_widget_id = dynamic_cast<QWidget*>(window)->winId();
    }

    void TaskbarThumbnail::EnableIconicPreview(bool enable) {
        BOOL fForceIconic = enable ? TRUE : FALSE;
        BOOL fHasIconicBitmap = enable ? TRUE : FALSE;

        DwmSetWindowAttribute(
            m_widget_id,
            DWMWA_FORCE_ICONIC_REPRESENTATION,
            &fForceIconic,
            sizeof(fForceIconic));


        DwmSetWindowAttribute(
            m_widget_id,
            DWMWA_HAS_ICONIC_BITMAP,
            &fHasIconicBitmap,
            sizeof(fHasIconicBitmap));

    }

    void TaskbarThumbnail::SetThumbnail(QPixmap thumbnail) {
        m_thumbnail = thumbnail;
    }

    bool TaskbarThumbnail::winEvent(MSG* message, long* result) {

        switch (message->message)
        {
        case WM_DWMSENDICONICTHUMBNAIL: {
                HBITMAP hbitmap = m_thumbnail.toWinHBITMAP();
                DwmSetIconicThumbnail(m_widget_id, hbitmap, 0);

                if (hbitmap) DeleteObject(hbitmap);
            }
            break;

        case WM_DWMSENDICONICLIVEPREVIEWBITMAP: {
                HBITMAP hbitmap = m_thumbnail.toWinHBITMAP();
                POINT point;
                point.x = 0; point.y = 0;

                DwmSetIconicLivePreviewBitmap(m_widget_id, hbitmap, &point, 0);
                if (hbitmap) DeleteObject(hbitmap);
            }
            break;
        default:
            return false;
        }

        return false;
    }


}

#endif //Q_OS_WIN32
