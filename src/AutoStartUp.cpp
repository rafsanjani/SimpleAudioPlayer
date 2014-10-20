#include "AutoStartUp.h"
/*accepts application name and optional path and adds it to the windows registry so
that application is launched automatically on windows startup*/
wxAutoStartUp::wxAutoStartUp(string appName,string path)
{
    pRegKey = new wxRegKey("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run");
    strAppName = appName;
    strAppPath = path;

    if(strAppName == wxT(""))
	{
		strAppName = wxTheApp->GetAppName();
	}

	if(strAppPath == wxT(""))
	{
		strAppPath = GetExecutablePath();
	}
}

//Adds or deletes the program from the windows startup list
bool wxAutoStartUp::AutoStartUp(bool bAdd)
{
 	if(!pRegKey->Exists())
    {
        delete pRegKey;
		return false;
	}

	if(bAdd)
    {
		if(!pRegKey->SetValue(strAppName, strAppPath))
		{
			delete pRegKey;
			return false;
		}
	}

	else
	{
		pRegKey->DeleteValue(strAppName);
	}

 	delete pRegKey;
	return true;
}

//checks if autostart is already set for the program
bool wxAutoStartUp::Exist()
{
    if(pRegKey->HasValue(strAppName))
        return true;
    else
        return false;
}

//Returns the absolute path of the executable in MSW
wxString wxAutoStartUp::GetExecutablePath()
{
    wxString path;
    TCHAR exePath[128];
    GetModuleFileName(NULL,exePath , 128);
    path = exePath;

    return path;
}
//RAFS
