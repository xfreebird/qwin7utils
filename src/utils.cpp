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

#include "utils.h"
#include <QDebug>
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


    void DwmEnableBlurBehindWindow(HWND hwnd, const DWM_BLURBEHIND* pBlurBehind) {
        HMODULE shell;

        shell = LoadLibrary(L"dwmapi.dll");
        if (shell) {
            t_DwmEnableBlurBehindWindow set_window_blur = reinterpret_cast<t_DwmEnableBlurBehindWindow>(GetProcAddress (shell, "DwmEnableBlurBehindWindow"));
            set_window_blur(hwnd, pBlurBehind);

            FreeLibrary (shell);
        }
    }

    void DwmExtendFrameIntoClientArea(HWND hwnd, const MARGINS *pMarInset) {
        HMODULE shell;

        shell = LoadLibrary(L"dwmapi.dll");
        if (shell) {
            t_DwmExtendFrameIntoClientArea set_window_frame_into_client_area = reinterpret_cast<t_DwmExtendFrameIntoClientArea>(GetProcAddress (shell, "DwmExtendFrameIntoClientArea"));
            set_window_frame_into_client_area(hwnd, pMarInset);

            FreeLibrary (shell);
        }

    }

    void ExtendFrameIntoClientArea(QWidget* widget) {
        MARGINS margins = {-1};

        DwmExtendFrameIntoClientArea(widget->winId(), &margins);
    }

    HRESULT EnableBlurBehindWidget(QWidget* widget, bool enable)
    {
        HWND hwnd = widget->winId();
        HRESULT hr = S_OK;

        widget->setAttribute(Qt::WA_TranslucentBackground, enable);
        widget->setAttribute(Qt::WA_NoSystemBackground, enable);

        // Create and populate the Blur Behind structure
        DWM_BLURBEHIND bb = {0};

        bb.dwFlags = DWM_BB_ENABLE;
        bb.fEnable = enable;
        bb.hRgnBlur = NULL;

        DwmEnableBlurBehindWindow(hwnd, &bb);
        return hr;
    }

}
