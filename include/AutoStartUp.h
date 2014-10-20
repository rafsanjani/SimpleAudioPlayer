/*AutoStartUp.h
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
********************************************************************/

#ifndef AUTOSTARTUP_H
#define AUTOSTARTUP_H

#include <wx/wx.h>
#include <wx/config.h>
using namespace std;
class wxAutoStartUp
{
public:
    wxAutoStartUp(string appName = "", string path = "");
    bool AutoStartUp(bool bAdd = true);
    bool Exist();

private:
    wxRegKey *pRegKey;
    wxString strAppName;
    wxString strAppPath;
    wxString GetExecutablePath();
};
#endif // AUTOSTARTUP_H



