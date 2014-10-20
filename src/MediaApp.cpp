#include "MediaApp.h"
#include "AutoStartUp.h"
#include "TagReader.h"

DECLARE_APP(MyApp)/*makes an object of MyApp available to this class*/
BEGIN_EVENT_TABLE(MediaFrame, wxFrame)
    EVT_LIST_ITEM_ACTIVATED(wxID_PLAYLIST, MediaFrame::OnChangeSong)

    EVT_KEY_DOWN(MediaFrame::OnKeyDown)

    EVT_BUTTON(wxID_PLAYBUTTON, MediaFrame::OnPlay)
    EVT_BUTTON(wxID_NEXT, MediaFrame::OnNext)
    EVT_BUTTON(wxID_PREV, MediaFrame::OnPrev)
    EVT_BUTTON(wxID_STOPBUTTON, MediaFrame::OnStop)

    EVT_MENU(wxID_PLAYBUTTON, MediaFrame::OnPlay)
    EVT_MENU(wxID_NEXT, MediaFrame::OnNext)
    EVT_MENU(wxID_PREV, MediaFrame::OnPrev)
    EVT_MENU(wxID_STOPBUTTON, MediaFrame::OnStop)
    EVT_MENU(wxID_OPEN, MediaFrame::OnOpenFile)
    EVT_MENU(wxID_SHUFFLE, MediaFrame::OnShuffle)
    EVT_MENU(wxID_REPEAT, MediaFrame::OnRepeat)
    EVT_MENU(wxID_SHOWPLAYLIST, MediaFrame::ShowPlaylist)
    EVT_MENU(wxID_AUTOSTART, MediaFrame::OnAutoStart)
    EVT_MENU(wxID_HIDE, MediaFrame::OnHide)
    EVT_MENU(wxID_CLOSE, MediaFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MediaFrame::OnAbout)

    EVT_TIMER(wxID_TIMER, MediaFrame::Notify)
    EVT_TIMER(wxID_CROSSFADETIMER, MediaFrame::DoCrossFade)
    EVT_CLOSE(MediaFrame::OnClose)
END_EVENT_TABLE()

MediaFrame::MediaFrame(wxWindow *parent,const wxString &title, wxPoint pos, wxSize size, long style)
        : wxFrame(parent, wxID_ANY, title, pos, size, style)
{
    LoadAllGuiControls();
}

void MediaFrame::LoadAllGuiControls()
{
    SetBitmaps();

    int freq = 44100;
    int device = -1; //use default audio device

    BASS_Init(device, freq, 0, NULL, NULL);

	//set background colour of the main frame to black
    SetBackgroundColour(wxColour("black"));

    //container for all other controls
    MyPanel *panel = new MyPanel(this);

    panel->SetBackgroundColour(wxColour("white"));
	//position an image onto the right side of the panel
    /*wxStaticBitmap *bmp = */new wxStaticBitmap(panel,wxID_ANY,headerImage, wxPoint(255, 25),wxDefaultSize);

    menuBar = new wxMenuBar();
    fileMenu = new wxMenu();
    optionMenu = new wxMenu();
    playBackMenu = new wxMenu();

    fileMenu->Append(wxID_OPEN,"Open","Open A file");
    fileMenu->Append(wxID_CLOSE,"Exit\tAlt+F4","Exit");

    playBackMenu->AppendCheckItem(wxID_SHUFFLE,"Shuffle\tCtrl+S","Play in shuffle mode");
    playBackMenu->AppendCheckItem(wxID_REPEAT,"Repeat\tCtrl+R","Repeat playing track");
    playBackMenu->Append(wxID_NEXT,"Next\tCtrl+N","Skip to next track");
    playBackMenu->Append(wxID_PREV,"Previous\tCtrl+P");

    playBackMenu->Append(wxID_PLAYBUTTON,"Play\tSPACE");

    playBackMenu->Append(wxID_STOPBUTTON, "Stop\tCtrl+T");

    optionMenu->AppendCheckItem(wxID_SHOWPLAYLIST,"Show Playlist","Show the playlist");
    optionMenu->Append(wxID_FILEINFO, "File Info","Complete File Info");
    optionMenu->Append(wxID_HIDE, "Pegasus");
    optionMenu->Append(wxID_ABOUT, "About","About");
    optionMenu->Append(wxID_PREFERENCES, "Preferences");

    menuBar->Append(fileMenu,"&File");
    menuBar->Append(playBackMenu,"&Playback");
    menuBar->Append(optionMenu, "&Options");
    SetMenuBar(menuBar);

    taskBarIcon = new MediaTaskBarIcon(this);
    taskBarIcon->SetIcon(wxICON(aaaaa), "Simple Audio Player");


    myTimer = new wxTimer(this, wxID_TIMER);
    crossFadeTimer = new wxTimer(this, wxID_CROSSFADETIMER);


    wxBoxSizer *sizer  = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *sizer2 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *mediaControls = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *sizer3 = new wxBoxSizer(wxHORIZONTAL);

     VolumeSlider = new wxSlider(panel, wxID_VOLSLIDER, 0, 0, 100,
                        wxDefaultPosition, wxSize(70,20), 0);

	//for updating track position
    seeker = new wxSlider(panel, wxID_SEEKER,0,0,100,
                          wxDefaultPosition, wxSize(250,20),0);
    seeker->Enable(false);

    Connect(wxID_SEEKER, wxEVT_SCROLL_THUMBTRACK,
                  wxScrollEventHandler(MediaFrame::OnBeginSeek));

    Connect(wxID_SEEKER, wxEVT_SCROLL_THUMBRELEASE,
                  wxScrollEventHandler(MediaFrame::OnEndSeek));

    Connect(wxID_VOLSLIDER, wxEVT_SLIDER,
            wxScrollEventHandler(MediaFrame::OnVolumeChange));

	//When a key is pressed
    wxTheApp->Connect(wxID_PLAYLIST, wxEVT_KEY_DOWN,
                  wxKeyEventHandler(MediaFrame::OnKeyDown),
                  (wxObject*)0, this);

    sizer->Add(panel, 1, wxEXPAND | wxALL, 5);

	//for displaying current track's status
    trackInfo = new wxStaticText(panel,wxID_ANY,"Track info here");

    playlist = new MediaPlaylist(this);

    playlist->Create(panel, wxID_PLAYLIST, wxDefaultPosition, wxDefaultSize,
                    wxLC_REPORT | wxSUNKEN_BORDER | wxLC_HRULES);

    playlist->SetBackgroundColour(wxColour(130,130,130));
    playlist->SetForegroundColour(*wxWHITE);


    playlist->SetDropTarget(new FileDropTarget(*playlist));
    panel->SetDropTarget(new FileDropTarget(*playlist));

    //display title and length of the items in the playlist
    playlist->AppendColumn("", wxLIST_FORMAT_CENTER, 35);
    playlist->AppendColumn("Title", wxLIST_FORMAT_LEFT, 245);
    playlist->AppendColumn("Length", wxLIST_FORMAT_CENTER, -1);

	//for updating the length and position of the playing track
    trackLength = new wxStaticText(panel,wxID_ANY,"0:00/ 0:00");

    sizer3->Add(seeker,0, wxALL, 5);
    sizer3->Add(trackLength,0, wxALL, 5);
    sizer3->Add(new wxStaticBitmap(panel,wxID_ANY,shuffleBitmap), 0, wxLEFT|wxBOTTOM|wxTOP, 5);
    sizer3->Add(new wxStaticBitmap(panel, wxID_ANY, repeatBitmap), 0, wxALL, 5);

    sizer2->Add(sizer3, 0, wxEXPAND | wxALL, 5);
    sizer2->Add(mediaControls,0,wxALL, 5);
    sizer2->Add(trackInfo, 0, wxLEFT, 5);
    sizer2->Add(playlist,1, wxEXPAND | wxALL, 5);

    //create media control buttons
    playButton = new wxButton(panel,wxID_PLAYBUTTON,"",wxDefaultPosition,
                              wxDefaultSize, wxBU_EXACTFIT | wxBORDER_NONE);
    playButton->SetToolTip(new wxToolTip("PLAY"));

    stopButton = new wxButton(panel,wxID_STOPBUTTON,"",wxDefaultPosition,
                              wxDefaultSize, wxBU_EXACTFIT | wxBORDER_NONE);
    stopButton->SetToolTip(new wxToolTip("STOP"));

    nextButton = new wxButton(panel,wxID_NEXT,"",wxDefaultPosition,
                              wxDefaultSize, wxBU_EXACTFIT | wxBORDER_NONE);
    nextButton->SetToolTip(new wxToolTip("NEXT"));

    prevButton = new wxButton(panel,wxID_PREV,"",wxDefaultPosition,
                              wxDefaultSize, wxBU_EXACTFIT | wxBORDER_NONE);
    prevButton->SetToolTip(new wxToolTip("PREVIOUS"));

    playButton->SetBitmap(playBitmap);
    playButton->SetBitmapCurrent(playHoverBitmap);

    nextButton->SetBitmap(nextBitmap);
    nextButton->SetBitmapCurrent(nextHoverBitmap);

    prevButton->SetBitmap(prevBitmap);
    prevButton->SetBitmapCurrent(prevHoverBitmap);

    stopButton->SetBitmap(stopBitmap);
    stopButton->SetBitmapCurrent(stopHoverBitmap);

    mediaControls->Add(VolumeSlider,0,wxALL, 5);
    mediaControls->Add(playButton,0,wxALL, 5);
    mediaControls->Add(stopButton,0,wxALL, 5);
    mediaControls->Add(prevButton,0,wxALL, 5);
    mediaControls->Add(nextButton,0,wxALL, 5);

    //Load settings to be used by the player on startup
    LoadSettings();

    panel->SetSizer(sizer2);
    panel->Layout();
    sizer2->Fit(panel);

    this->SetSizer(sizer);
    this->Layout();
    this->Center(wxBOTH);
    Refresh();
}
/*instantiate the AutoStart class and check if app is already in autostart entry in MSW, if it is, we
check the autostart checkbox option in the menu bar, else we leave it as it is (unchecked)
*/
void MediaFrame::OnAutoStart(wxCommandEvent &event)
{
    wxAutoStartUp *Auto = new wxAutoStartUp();
    if(optionMenu->IsChecked(wxID_AUTOSTART)){
        if(Auto->AutoStartUp())
            wxMessageBox("Program will Launch at Windows StartUp!!");
    }
    else{
        if(Auto->AutoStartUp(false))
            wxMessageBox("Auto Start Now Disabled");
    }
    delete Auto;
}
/*
Loads some basic settings for the program, such as the playlist,
last playing file and last media state et cetera from the windows Registry
*/
void MediaFrame::LoadSettings()
{
    wxConfigBase *myConfig = wxConfigBase::Get();
    if(myConfig != nullptr)
    {
        myConfig->SetRecordDefaults();
        wxString key, outstring;

        myConfig->SetPath("/Controls");
        screenPosition.x = myConfig->Read(wxT("pos.x"), 50);
        screenPosition.y = myConfig->Read(wxT("pos.y"), 50);
        myConfig->Read("Volume", &InitVol);
        myConfig->Read("Shuffle",&shuffle);
        if(!myConfig->Read("Repeat", &repeat))
            firstRun = true;

        myConfig->Read("ShowPlaylist", &showPlaylist);

		int failed = 0;
        if(!wxGetApp().m_params.empty()){
            for(size_t n = 0; n < wxGetApp().m_params.size(); n++)
        {


        if((reinterpret_cast<FileDropTarget*>(playlist))->IsFormatSupported(wxGetApp().m_params[n]))
			playlist->AddToPlayList(wxGetApp().m_params[n]);
		else
			failed++;
        }

		if(failed != 0){
            wxMessageBox(wxString::Format("%d Files couldn't be added\n Reason: Unsupported Format", failed));
		}
        //if a file/files was/were added from the commandline. we load the first file and begin playing it
        if(playlist->GetItemCount() != 0 )
        {
            nextFile = (*(wxString *)playlist->GetItemData(0));
            filePath = nextFile;

            //load the file and start playing it
            BASS_StreamFree(str);
            if((str = BASS_StreamCreateFile(FALSE, nextFile.t_str(), 0, 0, BASS_STREAM_PRESCAN))){
                myTimer->Start();
                IsMusicLoaded = true;
            }
        }
			/*if no file was loaded from the cmdline, we move into the registry to see if there is a previously
			saved list so that we can load*/
        }else{
            myConfig->SetPath("/Playlist");
            for(size_t i = 0; ; ++i){
                key.clear();
                key << i;
                if(!myConfig->Read(key, &outstring))
                    break;
                playlist->AddToPlayList(outstring);
                }
            myConfig->SetPath("/Controls");
            if(myConfig->Read("Last File", &outstring)){
                myConfig->Read("State", &mediaEndState);
                if(mediaEndState == "Playing" || mediaEndState == "Paused"){
                    myConfig->Read("Offset", &offset);
                    myConfig->Read("Length", &length);
                    myConfig->Read("LastFileId", &LastFileId);

                    if(LastFileId > playlist->GetItemCount()){
                        lastPlayed = false;
                    }else{
                        if(LastFileId == playlist->GetItemCount()){
                            LastFileId--;
                        }
                        lastPlayed = true;

                        BASS_StreamFree(str);
                        str = BASS_StreamCreateFile(FALSE, outstring.t_str(),0,0, BASS_STREAM_PRESCAN);
                        IsMusicLoaded = true;
                        myTimer->Start(500);
                    }
                }
            }
        }

        if(showPlaylist){
            optionMenu->Check(wxID_SHOWPLAYLIST, true);
            this->SetClientSize(390,400);
        }
        else{
            if(!firstRun)
                this->SetClientSize(390,128);
            else{
                optionMenu->Check(wxID_SHOWPLAYLIST, true);
                this->SetClientSize(390,400);
                }
        }
        if(shuffle)
            playBackMenu->Check(wxID_SHUFFLE, true);
        if(repeat)
            playBackMenu->Check(wxID_REPEAT, true);

        VolumeSlider->SetValue(InitVol);
        double volume = static_cast<double>(VolumeSlider->GetValue())/100;
        BASS_ChannelSetAttribute(str, BASS_ATTRIB_VOL, volume);
     }

}
//When repeat is checked from the menu bar, we keep looping current song until user turns it off
void MediaFrame::OnRepeat(wxCommandEvent &event)
{
    if(playBackMenu->IsChecked(wxID_SHUFFLE)){
        playBackMenu->Check(wxID_SHUFFLE, false);
        shuffle = false;
    }
    if(event.IsChecked())
        repeat = true;
    else
        repeat = false;
}
//when shuffle is checked from the menu bar, songs are played from the playlist in a random order
void MediaFrame::OnShuffle(wxCommandEvent &event)
{
    if(playBackMenu->IsChecked(wxID_REPEAT))
    {
        playBackMenu->Check(wxID_REPEAT,false);
        repeat = false;
    }

    if(event.IsChecked())
       shuffle = true;
    else
        shuffle = false;
}

/*performs associated functions based on the state of the program.
also responsible for updating the volume and seek sliders
*/
void MediaFrame::Notify(wxTimerEvent &event)
{
    if(GetMediaState() == "Stopped"){
         if(BASS_ChannelGetPosition(str, BASS_POS_BYTE) == BASS_ChannelGetLength(str, BASS_POS_BYTE)){
            mediaFinished();
         }
    }

     if(IsMusicLoaded){
        mediaLoaded();
    }

    if(IsMusicPlaying){
        mediaPlaying();
    }

    if(IsMusicPaused){
        mediaPaused();
    }

    if(IsMusicStopped){
        mediaStopped();
    }

    wxString duration, played;
    GetSongLength(str, duration, played);

    llLength = BASS_ChannelGetLength(str, BASS_POS_BYTE);
    llTell = BASS_ChannelGetPosition(str, BASS_POS_BYTE);
    seeker->SetRange(0, llLength/100);

    if(!IsBeingDragged){
        seeker->SetValue(llTell/100);
    }

    trackLength->SetLabel(played+"/"+duration);
}

/*
Initialize all the bitmap objects using their corresponding image resources from .rc file
*/
void MediaFrame::SetBitmaps()
{
	wxInitAllImageHandlers();
    playBitmap = wxBITMAP_PNG(PLAY);
    playHoverBitmap = wxBITMAP_PNG(PLAY_HOVER);
    pausedBitmap = wxBITMAP_PNG(PAUSED);
    pausedHoverBitmap = wxBITMAP_PNG(PAUSED_HOVER);
    stopBitmap = wxBITMAP_PNG(STOP);
    stopHoverBitmap = wxBITMAP_PNG(STOP_HOVER);
    nextBitmap = wxBITMAP_PNG(NEXT);
    nextHoverBitmap = wxBITMAP_PNG(NEXT_HOVER);
    prevBitmap = wxBITMAP_PNG(PREV);
    prevHoverBitmap = wxBITMAP_PNG(PREV_HOVER);
    headerImage = wxBITMAP_PNG(HEADER);
    shuffleBitmap = wxBITMAP_PNG(SHUFFLEBITMAP);
    repeatBitmap = wxBITMAP_PNG(REPEATBITMAP);
}
/*
If media is paused, change the playbutton's bitmap to reflect the changes.
*/
void MediaFrame::mediaPaused()
{
    taskBarIcon->SetIcon(wxICON(TASKPAUSE),m_paused+songTitle);

    playButton->SetBitmap(playBitmap);
    playButton->SetBitmapCurrent(playHoverBitmap);

    trackInfo->SetLabel(m_paused+songArtist+ "-"+ songTitle);
    IsMusicPaused = false;
}
/*If media is stopped by pressing the stop button, we change the playbutton's
bitmap accordingly
*/
void MediaFrame::mediaStopped()
{
    taskBarIcon->SetIcon(wxICON(TASKSTOP), "Rafs Simple Audio Player");
    seeker->Enable(false);
    BASS_ChannelSetPosition(str, 0, BASS_POS_BYTE);
    trackInfo->SetLabel(m_stopped+songTitle);
    playButton->SetBitmap(playBitmap);
    playButton->SetBitmapCurrent(playHoverBitmap);
    IsMusicStopped = false;
}
/*If the stop button is clicked, we trigger the EVT_MEDIA_STOP by stopping the
currently playing song.
*/
void MediaFrame::OnStop(wxCommandEvent &event)
{
    CrossFade();
}

void MediaFrame::CrossFade()
{
    BASS_ChannelGetAttribute(str,BASS_ATTRIB_VOL, &volBeforeCrossFade);
    crossVol = volBeforeCrossFade;
    crossFadeTimer->Start(100);
}

void MediaFrame::DoCrossFade(wxTimerEvent &event)
{
    if(crossVol > 0 ){
        crossVol-=0.10;
        BASS_ChannelSetAttribute(str,BASS_ATTRIB_VOL,crossVol);
    }
    else
    {
        BASS_ChannelSetAttribute(str,BASS_ATTRIB_VOL,volBeforeCrossFade);
        BASS_ChannelStop(str);
        IsMusicStopped = true;
        crossFadeTimer->Stop();
    }
}

//When the next button is pressed, we move to the next if not at the end of the list
void MediaFrame::OnNext(wxCommandEvent &event)
{
    if(playlist->GetItemCount() != 0){//prevent anything from happening when there is nothing in playlist.
        if(LastFileId > playlist->GetItemCount()){
		//Do nothing here
        } else {
            playlist->SetItemBackgroundColour(LastFileId, wxColour(130,130,130));
            }
        if(repeat){
            LastFileId++;
            DoChangeSong();
        }else{
            DoChangeSong();
            }
    }
}

/*if not at the beginning of the playlist,this method moves backward by one track
 when the prev button is pressed, (if shuffling, the last most recently played song is re-played )else, the last item in the
playlist is played.*/
void MediaFrame::OnPrev(wxCommandEvent &event)
{
    if(!playedItems.empty()){
        if(playlist->GetItemCount() != 0){
                if(LastFileId > playlist->GetItemCount()){
                    //do nothing here
            } else {
                playlist->SetItemBackgroundColour(LastFileId, wxColour(130,130,130));
                }

            if(repeat){
                LastFileId++;
                DoChangeSongPrev();
            }else{
                DoChangeSongPrev();
                }
        }
    }
}

/*open a file dialog when open is selected from the filemenu or if the play button is
clicked whilst the playlist is empty*/
void MediaFrame::OnOpenFile(wxCommandEvent &event)
{
    DoOpenFile();
}

void MediaFrame::DoOpenFile()
{
    bool startPlaying = playlist->GetItemCount();
    wxString wildCard = "Audio Files |**.mp3*";

    wxFileDialog *fileDlg = new wxFileDialog(this,"Choose File/Files",wxEmptyString,
                                          wxEmptyString, wildCard,
                                          wxFD_MULTIPLE);

    if(fileDlg->ShowModal() == wxID_OK){
            wxArrayString files;
            fileDlg->GetPaths(files);
        for(size_t index = 0; index < files.GetCount(); index++){
            playlist->AddToPlayList(wxFileName(files[index]).GetFullPath());
        }
        fileName = wxFileName(files[0]).GetName();
        if(!startPlaying){
            BASS_ChannelStop(str);
             BASS_StreamFree(str);
            if((str = BASS_StreamCreateFile(FALSE, files[0].t_str(), 0,0,BASS_STREAM_PRESCAN))){
                BASS_ChannelPlay(str, FALSE);
                IsMusicLoaded = true;
            }
        }
    }

}
/*If the media is playing i.e IsMusicPlaying is activated:
1. set the bitmaps of the play/pause button accordingly
2. set the background and text colour of the currently playing item in the playlist
   accordingly.
3. Ensure that the current playing item is visible on the screen
4. Show a balloon in the tray icon displaying the title and artist of the song playing.
*/
void MediaFrame::mediaPlaying()
{
    wxListItem item;
    item.SetId(LastFileId);
    playlist->EnsureVisible(item);

    playlist->LastFileId = LastFileId;

    wxString balloonMsg;
    if(songArtist.length() == 0)
         balloonMsg = songTitle;
    else
         balloonMsg = songArtist+" - "+songTitle;

    taskBarIcon->ShowBalloon("Simple Audio Player",balloonMsg, 800);
    taskBarIcon->SetIcon(wxICON(TASKPLAY), m_playing+songTitle);
    seeker->Enable(true);

    playButton->SetBitmap(pausedBitmap);
    playButton->SetBitmapCurrent(pausedHoverBitmap);
    playButton->SetToolTip(new wxToolTip("PAUSE"));

    if(playlist->GetItemCount() != 0 )
    {
        //wxMessageBox("control inside here");
        trackInfo->SetLabel(m_playing+songArtist+" - " +songTitle);
        playlist->SetItemBackgroundColour(LastFileId, wxColour(210,210,210));
    }

    IsMusicPlaying = false;
    IsMusicLoaded = false;
}



/* If the currently playing song ends naturally aka eof(), we move to the next file in
the playlist. if the just ended file is the last, we move to the top of the list. if it
is the only file in the playlist, it loops forever.
*/

void MediaFrame::mediaFinished()
{
    if(playlist->GetItemCount() != 0)
        DoChangeSong();
    else{
        BASS_ChannelSetPosition(str, 0, BASS_POS_BYTE);
        IsMusicStopped = true;
    }
}

//If we choose to reduce the program to the tray, we fade it out
void MediaFrame::OnHide(wxCommandEvent &event)
{
   ShowMainWindow(false);
}


//changes the playing song based on some criteria.
void MediaFrame::DoChangeSong()
{
    if(!repeat)
    {
       int currentPlaylistItems = playlist->GetItemCount();
       if(LastFileId > currentPlaylistItems || currentPlaylistItems == 1)
       {
            LastFileId--;
       }
       else
       {
           if(LastFileId == currentPlaylistItems)
                playlist->SetItemBackgroundColour(LastFileId-1, wxColour(130,130,130));
            else
                playlist->SetItemBackgroundColour(LastFileId, wxColour(130,130,130));

       }

        if(currentPlaylistItems != 0)
        {
            if(LastFileId+1 >= currentPlaylistItems)
            {
                LastFileId-=currentPlaylistItems;
                SkipTrack();
            }
            else
            {
                SkipTrack();
            }

        }

    }
    else //we are repeating
    {
        SkipTrack();
    }
}

/*If we are going back instead of forward, everything becomes the opposite of the next*/
void MediaFrame::DoChangeSongPrev()
{
 playlist->SetItemBackgroundColour(LastFileId,wxColour(130,130,130));
    if(shuffle){
        int sz = playedItems.size();
        if(sz != 1)
            LastFileId = playedItems[sz-2];
        else
            LastFileId = playedItems[1];

        playedItems.pop_back();

        wxString file = *((wxString*)playlist->GetItemData(LastFileId));

        BASS_StreamFree(str);
        str = BASS_StreamCreateFile(FALSE, file.t_str(),0,0, BASS_STREAM_PRESCAN);
        IsMusicLoaded = true;
        return;
    }

    int items = playlist->GetItemCount();

    if(items != 0){//is playlist empty?
        if(LastFileId-1 < 0){//Are we at the end of the list?
            LastFileId+=items;
            SkipTrack(false);
        }
        else
        {
            SkipTrack(false);
        }
    }
}

/*
To play files evenly in shuffle mode, this function is required.
We don't trust C++ random cos the output is not always as random
as we would expect because some files keep repeating themselves.With this
function, we are going to ensure that, all items in the playlist are played in
shuffle mode before replaying any item. 100% random but quite slower

Todo: Develop a more effective algorithm for this method to improve speed
*/
bool MediaFrame::ItemPlayed(int value)
{
    unsigned int items = playlist->GetItemCount();
    if(playedItems.size() == items){
        playedItems.clear();
    }
    if(playedItems.empty()){
        return false;
    }
    else
    {
    /*
    //perform a binary search on the element
    int first = 0, last = playedItems.size() - 1, middle;
    bool found = false;
    while(!found and first <= last)
    {
        middle = (first+last)/2;
        if(playedItems[middle] == value){
            found = true;
            return found;
        }
        else if(playedItems[middle] > value){
           last = middle - 1;
        }
        else{
            first = middle + 1;
        }
    }
        */
    for(std::vector <int>::iterator it = playedItems.begin(); it != playedItems.end(); it++){
        if (value == *it)
            return true;
            }
    }
    return false;
}
/*
Function for generating a random number. The upper limit is the
size of the playlist with the lower limit always 0, if the generated
number is associated with a played item, then we generate another
until an unplayed id is generated. slow but quite effective
*/
int MediaFrame::RandNum()
{
    int output;
    bool played = true;
    while(played)
	{
        PlaylistItemCount = playlist->GetItemCount();
        std::default_random_engine generator;
        generator.seed(time(NULL));
        std::uniform_int_distribution<int> distribution(0 , PlaylistItemCount-1);
        for(int a = 0; a < 2; a++)
		{
            output = distribution(generator);
		}
        played = ItemPlayed(output);
    }
    return output;
}
/*
If shuffle is on whilst skipping forward, we skip to a random
track, else, we skip to the next in relation to the currently playing track
*/
void MediaFrame::SkipTrack(bool Next)
{

    if(shuffle)
	{
        int randnum = RandNum();
        playedItems.push_back(randnum);
        LastFileId = randnum;

        nextFile = *((wxString*) playlist->GetItemData(LastFileId));
        //NextFileId = LastFileId;
        filePath = nextFile;

        BASS_StreamFree(str);
        if((str = BASS_StreamCreateFile(FALSE, nextFile.t_str(), 0, 0, BASS_STREAM_PRESCAN))){
           IsMusicLoaded = true;
           }
    }
    else if(repeat)
	{
        nextFile = *((wxString*)playlist->GetItemData(LastFileId));
        filePath = nextFile;

       BASS_StreamFree(str);
       if((str = BASS_StreamCreateFile(FALSE, nextFile.t_str(), 0, 0, BASS_STREAM_PRESCAN))){
           IsMusicLoaded = true;
           }
    }
    else
	{
        if(Next)
		{
            nextFile = *((wxString*) playlist->GetItemData(LastFileId+1));
            LastFileId++;
            filePath = nextFile;

            BASS_StreamFree(str);
            if((str = BASS_StreamCreateFile(FALSE, nextFile.t_str(), 0, 0, BASS_STREAM_PRESCAN))){
                IsMusicLoaded = true;
            }
            //NextFileId = LastFileId;
            playedItems.push_back(LastFileId);
        }
        else{//if previous
             LastFileId--;

             nextFile = *((wxString*) playlist->GetItemData(LastFileId));
             filePath = nextFile;

             BASS_StreamFree(str);
             playedItems.pop_back();

             if((str = BASS_StreamCreateFile(FALSE, nextFile.t_str(), 0, 0, BASS_STREAM_PRESCAN)))
                 IsMusicLoaded = true;
        }
    }
}


//returns the length of the currently playing track for displaying
void MediaFrame::GetSongLength(DWORD handle, wxString &duration, wxString &played)
{
    long len = (BASS_ChannelGetLength(handle, BASS_POS_BYTE));
    llLength = BASS_ChannelBytes2Seconds(handle, len);

    int secs = static_cast<int>(llLength)%60;
    int mins = (llLength - secs) / 60;

    duration.Printf(wxT("%2i:%02i"), mins, secs);

    len = BASS_ChannelGetPosition(handle, BASS_POS_BYTE);
    llTell = BASS_ChannelBytes2Seconds(handle, len);
    secs = static_cast<int>(llTell) % 60;
    mins = (llTell - secs)/60;

    played.Printf("%2i:%02i", mins, secs);

}

//if IsMusicLoaded is activated, then we play the song and also update some media controls
void MediaFrame::mediaLoaded()
{
    double volume = static_cast<double>(VolumeSlider->GetValue())/100;
    BASS_ChannelSetAttribute(str, BASS_ATTRIB_VOL, volume);

    wxString duration, played;
    GetSongLength(str, duration, played);

    playlist->SetItem(LastFileId, 2, duration);

    wxString currFile = *((wxString*) playlist->GetItemData(LastFileId));
    filePath = currFile;

    TagReader tags(filePath);
    if(tags.HasTags()){
        songTitle = tags.GetTitle();
        songArtist = tags.GetArtist();
    }

    if(songTitle.length() == 0 or songArtist.length() == 0)
        songTitle = wxFileName(filePath).GetName();

    if(lastPlayed)
    {
        //wxMessageBox("lastplayed");
        long foffset = offset;
        long flength = length;
        seeker->SetRange(0, flength / 100);
        seeker->SetValue(foffset / 100);

        if(mediaEndState == "Playing"){
            BASS_ChannelSetPosition(str, offset, BASS_POS_BYTE);
            BASS_ChannelPlay(str, FALSE);
            IsMusicPlaying = true;
        }
        if(mediaEndState == "Paused"){
            wxString played, duration;

            BASS_ChannelSetPosition(str, offset, BASS_POS_BYTE);
            BASS_ChannelSetAttribute(str, BASS_ATTRIB_VOL, 0);
            BASS_ChannelPlay(str, FALSE);
            BASS_ChannelPause(str);
            BASS_ChannelSetAttribute(str, BASS_ATTRIB_VOL, static_cast<double>(VolumeSlider->GetValue())/100);

            GetSongLength(str, duration, played);

            trackLength->SetLabel(played+"/"+duration);

            IsMusicPaused = true;
            IsMusicStopped = false;
    }
    else{
        BASS_ChannelPlay(str, FALSE);
        myTimer->Start(500);
        IsMusicStopped = false;
        IsMusicPaused = false;
    }
        lastPlayed = false;
    }
    else{
        BASS_ChannelPlay(str, FALSE);
        myTimer->Start(500);
        IsMusicStopped = false;
        IsMusicPaused = false;
    }

    IsMusicLoaded = false;
    IsMusicPlaying = true;
}
/*
if the play/pause button is clicked, we check the state in which the player is
before performing any action. if the media is paused then we resume it. if it is
stopped, we play it from the beginning. If the media is playing, then we pause it
*/
void MediaFrame::OnPlay(wxCommandEvent &event)
{
    DoPlaySong();
    myTimer->Start(500);
}

wxString MediaFrame::GetMediaState()
{
    unsigned state = BASS_ChannelIsActive(str);
    switch(state)
    {
        case 0:
            return "Stopped";
            break;

        case 1:
            return "Playing";
            break;

        case 2:
            return "Stalled";
            break;

        case 3:
            return  "Paused";
            break;

        default:
            wxMessageBox("There was an error reading media state");
            break;
    }
    return "UNKNOWN STATE";
}

void MediaFrame::DoPlaySong()
{
    wxString mediaState = GetMediaState();
    if(playlist->GetItemCount() != 0 )
    {
       if(mediaState == "Paused"){
            playButton->SetBitmap(pausedBitmap);
            BASS_ChannelPlay(str, FALSE);

            IsMusicPlaying = true;
            IsMusicPaused = false;
       }
       else if(mediaState == "Playing"){
            BASS_ChannelPause(str);
            playButton->SetBitmap(playBitmap);

            IsMusicPlaying = false;
            IsMusicPaused = true;
       }

       else if(mediaState == "Stopped"){
            wxListItem item;
            playlist->GetSelectedItem(item);

            int Id = item.GetId();
            playlist->SetItemBackgroundColour(LastFileId,wxColour(130,130,130));

            if(Id != -1)
            {
                LastFileId = Id;
                wxString file = (*(wxString*)playlist->GetItemData(LastFileId));

                 BASS_StreamFree(str);
                if((str = BASS_StreamCreateFile(FALSE, file.t_str(), 0, 0, BASS_STREAM_PRESCAN)))
                {
                    IsMusicLoaded = true;
                    playButton->SetBitmap(pausedBitmap);
                }
            }
            else
            {
                wxString file = (*(wxString*)playlist->GetItemData(LastFileId));

                 BASS_StreamFree(str);
                if((str = BASS_StreamCreateFile(FALSE, file.t_str(), 0, 0, BASS_STREAM_PRESCAN))){
                    BASS_ChannelPlay(str, true);
                }

                IsMusicLoaded = true;
                myTimer->Start();            }

            IsMusicStopped = false;
            }

    playlist->SetItemBackgroundColour(LastFileId, wxColour(210,210,210));

    }
    else
       DoOpenFile();
}


/*
when we double click an item in the playlist, or select an item and hit enter,
then we load it into the media.
Todo: change method name to OnActivateSong
*/
void MediaFrame::OnChangeSong(wxListEvent &event)
{
    BASS_ChannelStop(str);
    if(LastFileId <= playlist->GetItemCount())
    {
        if(LastFileId == playlist->GetItemCount())
            playlist->SetItemBackgroundColour(LastFileId-1, wxColour(130,130,130));
        else
            playlist->SetItemBackgroundColour(LastFileId, wxColour(130,130,130));
    }

    wxListItem item;
    playlist->GetSelectedItem(item);
    if(item.GetData())
    {
        wxString file = *((wxString*) item.GetData());
        LastFileId = item.GetId();

         BASS_StreamFree(str);
        if((str = BASS_StreamCreateFile(FALSE, file.t_str(), 0, 0, BASS_STREAM_PRESCAN))){
           myTimer->Start(500);
           IsMusicLoaded = true;
           }
    }
}

void MediaFrame::OnAbout(wxCommandEvent &event)
{
    ShowAbout();
}

void MediaFrame::ShowAbout()
{
    wxBitmap bitmap = wxBITMAP_PNG(SPLASH);

     new wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_NO_TIMEOUT | wxSPLASH_CENTRE_ON_PARENT,
                                6000, NULL, -1, wxDefaultPosition, wxDefaultSize,
                                wxBORDER_SIMPLE|wxSTAY_ON_TOP);
    wxYield();
}

void MediaFrame::OnClose(wxCloseEvent &evt)
{
    DoCloseFrame();
}

void MediaFrame::OnExit(wxCommandEvent &event)
{
    DoCloseFrame();
}

void MediaFrame::DoCloseFrame()
{
    HideFrame();
    Destroy();
}

void MediaFrame::HideFrame()
{
    this->HideWithEffect(wxSHOW_EFFECT_BLEND, 1000);
}

//when the volume slider is moved, we change the media volume accordingly
void MediaFrame::OnVolumeChange(wxScrollEvent &event)
{
    double m_vol  = static_cast<double>(VolumeSlider->GetValue())/100;
    BASS_ChannelSetAttribute(str, BASS_ATTRIB_VOL, m_vol);
}

//When the seek slider is moved we activate the IsBeingDragged flag
void MediaFrame::OnBeginSeek(wxScrollEvent& WXUNUSED(event))
{
    IsBeingDragged = true;
}

void MediaFrame::ShowMainWindow(bool Show)
{
	if(Show)
    {
		ShowWithEffect(wxSHOW_EFFECT_BLEND,800);
        if(IsIconized())
            Iconize(false);
	}
	else
		HideWithEffect(wxSHOW_EFFECT_BLEND, 800);
}

//when the seek slider is released, we seek the media to the appropriate position
void MediaFrame::OnEndSeek(wxScrollEvent &WXUNUSED(event))
{
    if(!(BASS_ChannelSetPosition(str, seeker->GetValue()*100, BASS_POS_BYTE)))
    {
        wxMessageBox("Invalid file offset");
    }
    IsBeingDragged = false;
}


//Whenever a key from the keyboard is pressed, we capture the event and check whether
//the key pressed is of importance to us. if not we skip the event.
void MediaFrame::OnKeyDown(wxKeyEvent& event)
{
    //save the keycode into a variable and use it to perform some useful jobs
    unsigned int pressedKey = event.GetKeyCode();
    switch(pressedKey)
    {
        case WXK_DELETE:
         playlist->DoDeleteItems();
         playlist->ArrangeQueue();
         break;

        case WXK_SPACE:
            if(GetMediaState() == "Playing")
                BASS_ChannelPause(str);
            else //it is either stopped or paused
                BASS_ChannelPlay(str, FALSE);
            break;

        case WXK_ESCAPE:
          if(playlist->GetItemCount() != 0 && GetMediaState() == "Playing")
                playlist->DoPhysicalDelete(true); //we are deleting the currently playing file from disk
            break;

        default:
            event.Skip();
            break;
        }//end of switch statements
}

//when show playlist is selected from the options menu
void MediaFrame::ShowPlaylist(wxCommandEvent &event)
{
    if(!event.IsChecked())
    {
        SetClientSize(390,128);
    }
    else
    {
        SetClientSize(390,400);
    }
}

//save all settings and the playlist when program is terminating
MediaFrame::~MediaFrame()
{
    wxConfigBase *myConfig = wxConfigBase::Get();
    if(myConfig != nullptr)
    {
        mediaEndState = GetMediaState();
        BASS_ChannelStop(str);

        taskBarIcon->RemoveIcon();
        delete taskBarIcon;

        myConfig->DeleteAll();
        if (myConfig == NULL)
            return;
        myConfig->SetPath("/Playlist");
        for(int i = 0; i < playlist->GetItemCount(); ++i)
        {
            wxString *pData = (wxString*) playlist->GetItemData(i);
            wxString s;
            s << i;
            myConfig->Write(s, *(pData));
            delete pData;
        }

        int length = BASS_ChannelGetLength(str, BASS_POS_BYTE);

        myConfig->SetPath("../Controls");
        if(filePath.size() != 0 && playlist->GetItemCount() != 0)
        {
            offset = BASS_ChannelGetPosition(str, BASS_POS_BYTE);
            length = BASS_ChannelGetLength(str, BASS_POS_BYTE);
            myConfig->Write("Last File",filePath);
            myConfig->Write("State",mediaEndState);
            myConfig->Write("Offset", offset);
            myConfig->Write("Length", length);
            myConfig->Write("LastFileId", LastFileId);
        }
		wxPoint pos = GetPosition();
        myConfig->Write("pos.x",pos.x);
        myConfig->Write("pos.y",pos.y);

        myConfig->Write("Volume",VolumeSlider->GetValue());
        myConfig->Write("Shuffle", shuffle);
        myConfig->Write("Repeat",repeat);
        myConfig->Write("ShowPlaylist",optionMenu->IsChecked(wxID_SHOWPLAYLIST));
        delete myTimer;
        return;
    }
    BASS_StreamFree(str);
}
//RAFS
