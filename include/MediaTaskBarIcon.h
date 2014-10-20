#ifndef MEDIATASKBARICON_H
#define MEDIATASKBARICON_H

/*MediaTaskBarIcon.h
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
#include <wx/taskbar.h>
#include <wx/splash.h>

//inherits wxTaskBarIcon class
class MediaTaskBarIcon : public wxTaskBarIcon
{
    public:
        wxWindow *parent;
        MediaTaskBarIcon(wxWindow *parent);
        virtual ~MediaTaskBarIcon();

    private:
        virtual wxMenu *CreatePopupMenu();
        void OnMenuPlay(wxCommandEvent &WXUNUSED(event));
        void OnMenuPause(wxCommandEvent &WXUNUSED(event));
        void OnMenuStop(wxCommandEvent &WXUNUSED(event));
        void OnMenuExit(wxCommandEvent& WXUNUSED(event));
        void OnMenuAbout(wxCommandEvent& WXUNUSED(event));
        void OnMenuRestore(wxCommandEvent& WXUNUSED(event));
        void OnLeftButtonDClick(wxTaskBarIconEvent &event);
        void OnMenuNext(wxCommandEvent &event);
        void OnMenuPrev(wxCommandEvent &event);

private:

	DECLARE_EVENT_TABLE()
};
enum
{
    MenuExit = 5000,
    MenuHide,
    MenuAbout,
    MenuRestore,
    MenuPlay,
    MenuPause,
    MenuStop,
    MenuNext,
    MenuPrev
};

#endif // MEDIATASKBARICON_H
