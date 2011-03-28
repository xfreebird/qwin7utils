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

#ifndef UTILS_H
#define UTILS_H

#include <QWidget>

#ifdef Q_OS_WIN32
#include <windows.h>

#define DWM_BB_ENABLE                 0x00000001  // fEnable has been specified

namespace QW7 {

    typedef struct _DWM_BLURBEHIND
    {
        DWORD dwFlags;
        BOOL fEnable;
        HRGN hRgnBlur;
        BOOL fTransitionOnMaximized;
    } DWM_BLURBEHIND, *PDWM_BLURBEHIND;

    typedef struct _MARGINS
    {
        int cxLeftWidth;      // width of left border that retains its size
        int cxRightWidth;     // width of right border that retains its size
        int cyTopHeight;      // height of top border that retains its size
        int cyBottomHeight;   // height of bottom border that retains its size
    } MARGINS, *PMARGINS;

    extern "C"
    {
        typedef HRESULT (WINAPI *t_DwmSetIconicThumbnail)(HWND hwnd, HBITMAP hbmp, DWORD dwSITFlags);
        typedef HRESULT (WINAPI *t_DwmSetWindowAttribute)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
        typedef HRESULT (WINAPI *t_DwmSetIconicLivePreviewBitmap)(HWND hwnd, HBITMAP hbmp, POINT *pptClient, DWORD dwSITFlags);
        typedef HRESULT (WINAPI *t_DwmEnableBlurBehindWindow)(HWND hWnd, const DWM_BLURBEHIND* pBlurBehind);
        typedef HRESULT (WINAPI *t_DwmExtendFrameIntoClientArea)(HWND hwnd, const MARGINS *pMarInset);
    }

    void DwmSetIconicThumbnail(HWND hwnd, HBITMAP hbmp, DWORD dwSITFlags);
    void DwmSetWindowAttribute(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
    void DwmSetIconicLivePreviewBitmap(HWND hwnd, HBITMAP hbmp, POINT *pptClient, DWORD dwSITFlags);
    void DwmEnableBlurBehindWindow(HWND hwnd, const DWM_BLURBEHIND* pBlurBehind);
    void DwmExtendFrameIntoClientArea(HWND hwnd, const MARGINS *pMarInset);

    void ExtendFrameIntoClientArea(QWidget* widget);
    HRESULT EnableBlurBehindWidget(QWidget* widget, bool enable);
}

#endif //Q_OS_WIN32

#endif // UTILS_H
