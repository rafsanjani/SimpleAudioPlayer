/*Playlist.h
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

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <wx/listctrl.h>
#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/utils.h>

class MediaPlaylist : public wxListCtrl
{
   public:
   //pointer to the parent window instantiating the control so we can fire events back to it
    wxWindow *parent;
    MediaPlaylist(wxWindow *parent);
    int LastFileId;
   public:
    void ArrangeQueue();
    void DoDeleteItems();
    void DoPhysicalDelete(bool currentFile = false);
    void AddToPlayList(const wxString &szString);
    void GetSelectedItem(wxListItem &listitem);
    void OnRightDown(wxMouseEvent &evt);
    void OnLeftDown(wxMouseEvent &evt);
    void Clear(wxCommandEvent &event);
    void Delete(wxCommandEvent &event);
    void OnPhysicalDelete(wxCommandEvent &event);
    void OnInfo(wxCommandEvent &event);
    int fileId;

   private:
    DECLARE_EVENT_TABLE()
};

#endif // PLAYLIST_H
