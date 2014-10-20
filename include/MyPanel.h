#ifndef MYPANEL_H
#define MYPANEL_H

/*MyPanel.h
* Copyright 2014 Aziz Rafsanjani
* http://foreverraf.tk/
*
* This file is part of Simple Audio Player.
*
* Simple Audio Player is free software: you can redistribute it and/or modify it under the
* terms of the GNU General Public License as published by the Free Software
* Foundation, either version 3 of the License, or (at your option) any later
* version.
*
* Simple Audio Player is distributed in the hope that it will be useful, but WITHOUT ANY
* WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
* A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* Simple Audio Player.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <wx/wx.h>

//To allow dragging from any part of the program other than the Titlebar,
//we derive a class from wxPanel and catch all the mouse events
class MyPanel : public wxPanel
{
    public:
        friend class MediaFrame;
        wxFrame *parent;
        MyPanel(wxFrame *parent);
        virtual ~MyPanel();

    private:
        wxPoint m_delta;
        void OnLeftDown(wxMouseEvent &event);
        void OnLeftUp(wxMouseEvent &event);
        void OnMouseMove(wxMouseEvent &event);
    protected:
        DECLARE_EVENT_TABLE()
};

#endif // MYPANEL_H
