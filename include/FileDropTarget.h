#ifndef FILEDROPTARGET_H
#define FILEDROPTARGET_H

/*FileDropTarget.h
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
#include <wx/dir.h>
#include <wx/dnd.h>
#include <wx/listctrl.h>
#include "Playlist.h"
class FileDropTarget : public wxFileDropTarget
{
    public:
        FileDropTarget(MediaPlaylist &m_listCtrl);
        bool IsFormatSupported(wxString fileName);

    private:
        MediaPlaylist &m_list;
        virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& files);

};

#endif // FILEDROPTARGET_H
