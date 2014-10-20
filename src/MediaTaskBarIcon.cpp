#include "MediaTaskBarIcon.h"
#include "MediaApp.h"
//MediaTaskBarIcon events. could have used this->Connect but event tables make things beautiful, besides
//there is no dynamic event
BEGIN_EVENT_TABLE(MediaTaskBarIcon, wxTaskBarIcon)
   EVT_MENU(MenuRestore, MediaTaskBarIcon::OnMenuRestore)
   EVT_MENU(MenuAbout, MediaTaskBarIcon::OnMenuAbout)
   EVT_MENU(MenuExit, MediaTaskBarIcon::OnMenuExit)
   EVT_MENU(MenuPlay, MediaTaskBarIcon::OnMenuPlay)
   EVT_MENU(MenuPause, MediaTaskBarIcon::OnMenuPause)
   EVT_MENU(MenuStop, MediaTaskBarIcon::OnMenuStop)
   EVT_MENU(MenuNext, MediaTaskBarIcon::OnMenuNext)
   EVT_MENU(MenuPrev, MediaTaskBarIcon::OnMenuPrev)
   EVT_TASKBAR_LEFT_DCLICK(MediaTaskBarIcon::OnLeftButtonDClick)
END_EVENT_TABLE()
//constructor accepts a pointer to the window instantiating the class so that we can send signals back to it
MediaTaskBarIcon::MediaTaskBarIcon(wxWindow *parent)
{
    this->parent = parent;
}

void MediaTaskBarIcon::OnMenuRestore(wxCommandEvent &WXUNUSED(event))
{
    if(((MediaFrame *)parent)->IsShown())
		((MediaFrame *)parent)->ShowMainWindow(false);
	else
		((MediaFrame *)parent)->ShowMainWindow();
}

void MediaTaskBarIcon::OnMenuPlay(wxCommandEvent &WXUNUSED(event))
{
     ((MediaFrame*)parent)->myTimer->Start(500);
     ((MediaFrame*)parent)->DoPlaySong();
}

void MediaTaskBarIcon::OnMenuStop(wxCommandEvent &WXUNUSED(event))
{
    BASS_ChannelStop( ((MediaFrame *) parent)->str);
     ((MediaFrame *) parent)->IsMusicStopped = true;
}
void MediaTaskBarIcon::OnMenuPause(wxCommandEvent &WXUNUSED(event))
{
   BASS_ChannelPause(((MediaFrame *) parent)->str);
    ((MediaFrame *) parent)->IsMusicPaused = true;
}
wxMenu *MediaTaskBarIcon::CreatePopupMenu()
{
    wxMenu *menu = new wxMenu(wxBORDER_NONE);
    wxMenuItem *restore = new wxMenuItem(menu,MenuRestore,"Show");
    wxMenuItem *pause = new wxMenuItem(menu,MenuPause,"Pause");
    wxMenuItem *play = new wxMenuItem(menu,MenuPlay,"Play");
    wxMenuItem *next = new wxMenuItem(menu, MenuNext, "Next");
    wxMenuItem *prev = new wxMenuItem(menu, MenuPrev, "Prev");
    wxMenuItem *about = new wxMenuItem(menu,MenuAbout,"About");
    wxMenuItem *exit = new wxMenuItem(menu,MenuExit,"Exit");
    wxMenuItem *hide = new wxMenuItem(menu,MenuRestore,"Hide");
    wxMenuItem *stop = new wxMenuItem(menu,MenuStop,"Stop");

    restore->SetBackgroundColour(wxColour(255,255,255));
    restore->SetTextColour(wxColour("black"));

    play->SetBackgroundColour(wxColour(255,255,255));
    play->SetBitmap(wxBITMAP_PNG(TASKMENUPLAY));
    play->SetTextColour(wxColour("black"));

    stop->SetBackgroundColour(wxColour(255,255,255));
    stop->SetBitmap(wxBITMAP_PNG(TASKMENUSTOP));
    stop->SetTextColour(wxColour("black"));

    pause->SetBackgroundColour(wxColour(255,255,255));
    pause->SetBitmap(wxBITMAP_PNG(TASKMENUPAUSE));
    pause->SetTextColour(wxColour("black"));

    about->SetBackgroundColour(wxColour(255,255,255));
    about->SetTextColour(wxColour("black"));

    exit->SetBackgroundColour(wxColour(255,255,255));
    exit->SetBitmap(wxBITMAP_PNG(TASKMENUCLOSE));
    exit->SetTextColour(wxColour("black"));

    hide->SetBackgroundColour(wxColour(255,255,255));
    hide->SetTextColour(wxColour("black"));

    next->SetBackgroundColour(wxColour(255,255,255));

    prev->SetBackgroundColour(wxColour(255,255,255));


	if(parent->IsShown())
		menu->Append(hide);
	else
		menu->Append(restore);


    //if(((MediaFrame *) parent)->media->GetState() != wxMEDIASTATE_PLAYING)
    if( ((MediaFrame *) parent)->GetMediaState() != "Playing")
        menu->Append(play);
    else
        menu->Append(pause);

    menu->Append(next);
    menu->Append(prev);

    menu->Append(stop);
    menu->Append(about);
    menu->Append(exit);

    return menu;
}

void MediaTaskBarIcon::OnMenuExit(wxCommandEvent &WXUNUSED(event))
{
    ((MediaFrame *)parent)->DoCloseFrame();
}

void MediaTaskBarIcon::OnLeftButtonDClick(wxTaskBarIconEvent &event)
{
    ((MediaFrame *) parent)->ShowMainWindow();
}

void MediaTaskBarIcon::OnMenuAbout(wxCommandEvent &event)
{
    ((MediaFrame *)parent)->ShowAbout();

}

void MediaTaskBarIcon::OnMenuNext(wxCommandEvent &event)
{
    ((MediaFrame *)parent)->DoChangeSong();
}
void MediaTaskBarIcon::OnMenuPrev(wxCommandEvent &event)
{
    ((MediaFrame *)parent)->DoChangeSongPrev();
}
MediaTaskBarIcon::~MediaTaskBarIcon()
{
}
//RAFS
