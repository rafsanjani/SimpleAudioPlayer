/** MediaApp.h
Main Frame Class
*********************************************************************************************************************************
/*
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
************************************************************************************************/

#ifndef MEDIAAPP_H
#define MEDIAAPP_H
#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/mediactrl.h>
#include <wx/tooltip.h>
#include "FileDropTarget.h"
#include "MediaTaskBarIcon.h"
#include "MediaMain.h"
#include "MyPanel.h"
#include <wx/colour.h>
#include <wx/config.h>
#include <wx/taskbar.h>
#include <random>
#include <vector>
#include <wx/vector.h>
#include "MyPanel.h"
#include "bass.h"
class MediaFrame : public wxFrame
{
    friend class MediaTaskBarIcon;
    friend void MediaPlaylist::DoPhysicalDelete(bool currentFile);
    friend bool MyApp::OnInit();
public:
    MediaFrame(wxWindow *parent,const wxString &title, wxPoint pos, wxSize size, long style = wxDEFAULT_FRAME_STYLE);

private:
    HSTREAM str;
    wxPoint screenPosition;
    //int clientHeight, clientWidth;
    bool  IsBeingDragged = false, showPlaylist = false, shuffle = false,
          repeat = false, lastPlayed = false,lastPaused = false, firstRun = false,
          IsMusicPlaying, IsMusicLoaded = false, IsMusicStopped = true,
          IsMusicPaused = false;

    int   PlaylistItemCount,LastFileId, prevFileId,
          NextFileId, offset, length, InitVol = 50, type;
    float volBeforeCrossFade, crossVol;

    std::vector <int> playedItems;
   // std::vector <int> nextItems;
   //std::vector <int> prevItems;
   // std::vector <int>::iterator it;
    long llLength, llTell;

    wxBitmap playBitmap, playHoverBitmap, pausedBitmap, pausedHoverBitmap,
             stopBitmap, stopHoverBitmap, nextBitmap, nextHoverBitmap,
             prevBitmap, prevHoverBitmap, headerImage,taskMenuPlay, shuffleBitmap,
             repeatBitmap;

    wxTimer *myTimer, *crossFadeTimer;
    wxSlider *VolumeSlider, *seeker;
    wxMediaCtrl *media;
    wxStaticText *trackInfo, *trackLength;
    MediaPlaylist *playlist;
    wxString fileName, filePath, nextFile, mediaEndState, songTitle, songArtist;
    const wxString m_playing = "Playing: ";
    const wxString m_stopped = "Stopped: ";
    const wxString m_paused = "Paused: ";
    wxButton *playButton, *stopButton, *nextButton, *prevButton;
    wxMenuBar *menuBar;
    wxMenu *fileMenu, *optionMenu, *playBackMenu;
    MediaTaskBarIcon *taskBarIcon;

private: //just separating functions from objects and variables
	int  RandNum();
    void LoadAllGuiControls();
    void SetBitmaps();
    void LoadSettings();
    //wxString GetState();
    wxString GetMediaState();
    void SkipTrack(bool Next = true);
   // void GetSongLength(wxString &m_played, wxString &m_duration);

    void DoChangeSong();
    void ShowAbout();
    void DoChangeSongPrev();
    void DoOpenFile();
    void DoPlaySong();
    void ArrangeQueue();
    void HideFrame();
    void DoCloseFrame();
    void CrossFade();
    void DoCrossFade(wxTimerEvent &event);
    void ShowMainWindow(bool Show = true);
    bool ItemPlayed(int item);

    //wxString msg, msg2;//for showing debugging messages

    void ShowPlaylist(wxCommandEvent &event);
    void OnOpenFile(wxCommandEvent &event);
    void OnPlay(wxCommandEvent &event);
    void OnPrev(wxCommandEvent &event);
    void OnNext(wxCommandEvent &event);
    void OnStop(wxCommandEvent &event);
    void OnShuffle(wxCommandEvent &event);
    void OnRepeat(wxCommandEvent &event);
    void OnAutoStart(wxCommandEvent &event);
    void OnHide(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);

    /*wxPoint m_delta;
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);*/

    void OnVolumeChange(wxScrollEvent &event);
    void OnBeginSeek(wxScrollEvent& WXUNUSED(event));
    void OnEndSeek(wxScrollEvent& WXUNUSED(event));

    //void mediaLoaded(wxMediaEvent &event);
    void mediaLoaded();
    //void mediaPlaying(wxMediaEvent &event);
    void mediaPlaying();

    //bool IsPlaying();
    //bool IsPaused();
    //bool IsStopped();
    //bool IsStalled();
    //void mediaFinished(wxMediaEvent &event);
    void mediaFinished();
    //void mediaStopped(wxMediaEvent &event);
    void mediaStopped();
   // void mediaPaused(wxMediaEvent &event);
    void mediaPaused();

    void GetSongLength(DWORD handle, wxString &duration, wxString &played);

	void OnChangeSong(wxListEvent &event);
	void OnClose(wxCloseEvent &evt);
    void OnKeyDown(wxKeyEvent &event);
    void Notify(wxTimerEvent &event);

protected:
    ~MediaFrame();
    DECLARE_EVENT_TABLE()
};

enum controlIds
{
    //some ids such as wxID_PLAY and wxID_STOP are standard ids but it is better to
    //make our own custom ids because of the nature of the buttons we are creating
    wxID_PLAYBUTTON = 1000,
    wxID_STOPBUTTON,
    wxID_PAUSE,
    wxID_SEEKER,
	wxID_MEDIACTRL,
	wxID_PMEDIA,
	wxID_TIMER,
	wxID_VOLSLIDER,
	wxID_PLAYLIST,
	wxID_NEXT,
	wxID_PREV,
	wxID_SHUFFLE,
	wxID_REPEAT,
	wxID_AUTOSTART,
	wxID_SHOWPLAYLIST,
	wxID_HIDE,
	wxID_FILEINFO,
	wxID_CROSSFADETIMER,
	ID_DUMMYVALUE
};

#endif // MEDIAAPP_H
