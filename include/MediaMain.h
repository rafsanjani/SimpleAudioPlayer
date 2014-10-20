/* MediaMain.h
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
 #ifndef MEDIAMAIN_H
 #define MEDIAMAIN_H

#include <wx/wx.h>
#include <wx/platinfo.h>
#include <wx/snglinst.h>
#include <wx/cmdline.h>
#include <wx/vector.h>
//inherits wxApp class. every wx Application must inherit this class
class MyApp : public wxApp
{
   // friend class MediaFrame;
public:
    virtual bool OnInit();
    wxVector <wxString> m_params;

private:
    virtual void OnInitCmdLine(wxCmdLineParser& parser);
    virtual bool OnCmdLineParsed(wxCmdLineParser& parser);

    const wxString AppName = "Simple Audio Player";
	//catch hibernation and shut down events from the computer
    void OnHibernate(wxActivateEvent &event);
    void OnEndSession(wxCloseEvent &event);
protected:
    DECLARE_EVENT_TABLE()
};



#endif // MEDIAMAIN_H
