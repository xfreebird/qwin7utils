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

#ifndef TASKBARBUTTON_H
#define TASKBARBUTTON_H

#include <QIcon>
#include <QString>
#include <QWidget>
#include <QList>
#include <QPixmap>

#ifdef Q_OS_WIN32
namespace QW7 {

    typedef enum TB_STATE {
        STATE_NOPROGRESS = 0x0,
        STATE_INDETERMINATE = 0x1,
        STATE_NORMAL = 0x2,
        STATE_ERROR = 0x4,
        STATE_PAUSED = 0x8
    } TB_STATE;

    class TaskbarButton : public QObject {

        Q_OBJECT
    private:
        WId m_widget_id;
        struct PrivateData;
        PrivateData* m_private;


    public:
        explicit TaskbarButton(QObject *parent);
        void Init();

        void createCustomToolbar(QList<QPixmap>& images);
        ~TaskbarButton();

    public slots:
        long SetOverlayIcon(const QIcon& icon, QString description);

        long SetState(TB_STATE state);
        long SetProgresValue(unsigned long long done, unsigned long long total);
    };
}
#endif // Q_OS_WIN32
#endif // TASKBARBUTTON_H
