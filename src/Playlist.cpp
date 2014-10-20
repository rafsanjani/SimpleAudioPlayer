#include "Playlist.h"
#include "MediaApp.h"
#include "TagReader.h"
//playlist popup menu events
BEGIN_EVENT_TABLE(MediaPlaylist, wxListCtrl)
    EVT_RIGHT_DOWN(MediaPlaylist::OnRightDown)
    EVT_MENU(wxID_CLEAR,MediaPlaylist::Clear)
    EVT_MENU(wxID_INFO, MediaPlaylist::OnInfo)
    EVT_MENU(wxID_REMOVE,MediaPlaylist::Delete)
    EVT_MENU(wxID_DELETE, MediaPlaylist::OnPhysicalDelete)
    EVT_LEFT_UP(MediaPlaylist::OnLeftDown)
END_EVENT_TABLE()

//constructor accepts a pointer to the control instantiating it (wxMediaCtrl) so that we send back signals through
//the pointer to the control
MediaPlaylist::MediaPlaylist(wxWindow *parent)
{
    this->parent = parent;
}

void MediaPlaylist::OnLeftDown(wxMouseEvent &evt)
{
   wxListItem item;
   GetSelectedItem(item);
   item.GetId();
}

//when we choose to delete an item(s) from the popup menu in the playlist
void MediaPlaylist::Delete(wxCommandEvent &event)
{
    DoDeleteItems();
    ArrangeQueue();
}
void MediaPlaylist::DoDeleteItems()
{
	//this will always be true at first iteration
    while(true)
       {
        wxInt32 nSelectedItem = GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		//if nSelectedItem is -1, then it means no item is selected or there is no item left to be deleted
		//so we exit out of the loop
           if (nSelectedItem == -1){
               break;
           }
           wxListItem listitem;
           listitem.SetId(nSelectedItem);
           GetItem(listitem);

           delete (wxString*) listitem.GetData();
           DeleteItem(nSelectedItem);
       }
	   //refresh the playlist after everything
       Refresh();
}
//when we choose clear from the popupmenu in the playlist, we delete all items from the playlist
void MediaPlaylist::Clear(wxCommandEvent &event)
{
    DeleteAllItems();
}
//when we rightclick in the playlist, we present the user with a popup menu with three options
void MediaPlaylist::OnRightDown(wxMouseEvent &evt)
{
    wxListItem item;
    GetSelectedItem(item);

    wxMenu *menu = new wxMenu();
    menu->Append(wxID_INFO, "File Info");
    menu->Append(wxID_REMOVE,"Remove");
    menu->Append(wxID_CLEAR,"Clear");

    if(item.GetId() != -1)
        menu->Append(wxID_DELETE,"Physically Delete");

    PopupMenu(menu);
}
//
void MediaPlaylist::AddToPlayList(const wxString& szString)
{
    wxString author, title, length;
    //GetTagInfo(szString, length, title, author);
    TagReader tags(szString);
    if(tags.HasTags()){
        title = tags.GetTitle();
        length = tags.GetTime();
        author = tags.GetArtist();
    }

    wxListItem kNewItem;
    kNewItem.SetAlign(wxLIST_FORMAT_LEFT);
    fileId = GetItemCount();
    kNewItem.SetId(fileId);
    kNewItem.SetMask(wxLIST_MASK_DATA);
    kNewItem.SetData(new wxString(szString));

    InsertItem(kNewItem);
    SetItem(fileId,0,wxString::Format("%d", fileId+1));//+1 to prevent numbering first item as 0
        //SetItem(fileId, 1, wxFileName(szString).GetName());
    if(title.size()!= 0 )
    {
        SetItem(fileId,1, title);
    }
    else
    {
        SetItem(fileId, 1, wxFileName(szString).GetName());
    }

    SetItem(fileId,2, length);

    //Refresh();
}

void MediaPlaylist::OnInfo(wxCommandEvent &event)
{
    wxListItem item;
    GetSelectedItem(item);
	if(item.GetId() != -1)
	{
		wxString file, title, artist, album, bitrate, genre, tracksize, year, samplerate, length, comment;
		file = (*(wxString*)item.GetData());


		double mb = (wxFileName(file).GetSize().ToDouble()/1024)/1024;

		tracksize = wxString::Format("%f", mb);
		wxString tracksize_n = (wxString::Format("%f", mb)).substr(0, 3);


		TagReader *tag = new TagReader(file);
		if(tag->HasTags()){
		    title = tag->GetTitle();
            artist = tag->GetArtist();
            album = tag->GetAlbum();
            bitrate = tag->GetBitrate();
            genre = tag->GetGenre();
            samplerate = tag->GetSamplerate();
            year = tag->GetYear();


            wxMessageBox("Title - "+title+"\nAuthor - "+artist+"\nAlbum - "+album+"\nBitrate - "+bitrate+"kbps"+
                         "\nGenre - "+genre+"\nSize - "+tracksize_n+"MB\nLength - "+length+"\nSample Rate - "+samplerate+
                         "\nYear - "+year+"\nFile - "+file, "Track Info ", wxOK);
            delete tag;
		}
	}

}

//if an item from the Playlist has focus, we get some data from it and save it into a variable
void MediaPlaylist::GetSelectedItem(wxListItem &listitem)
{
    listitem.SetMask(wxLIST_MASK_TEXT |  wxLIST_MASK_DATA);
    int nLast = -1, nLastSelected = -1;
    while ((nLast = GetNextItem(nLast,
                                wxLIST_NEXT_ALL,
                                wxLIST_STATE_SELECTED)) != -1)
    {
        listitem.SetId(nLast);
        GetItem(listitem);
        if ((listitem.GetState() & wxLIST_STATE_FOCUSED) )
            break;
        nLastSelected = nLast;
    }
    if (nLast == -1 && nLastSelected == -1)
        return;
    listitem.SetId(nLastSelected == -1 ? nLast : nLastSelected);
    GetItem(listitem);
}

//rearranges the playlist when an item is deleted or an item is inserted into the playlist in order to queue accordingly
void MediaPlaylist::ArrangeQueue()
{
	//save all the items in the playlist into a variable
    int MediaPlaylistItemCount = GetItemCount();
	//redundant vars
    //wxString file, artist, song;

	//if there is an item in the playlist, then we loop through and just change the numbers to arrange properly.
    if(MediaPlaylistItemCount != 0 ){
    for (int a = 0; a < MediaPlaylistItemCount; a++){
        SetItem(a, 0, wxString::Format("%d", a+1));//+1 to prevent numbering from 0
        }
    }
    //RefreshItems(0, GetItemCount());
}
//when we choose "physical delete" from the popup menu, we invoke DoPhysicalDelete
void MediaPlaylist::OnPhysicalDelete(wxCommandEvent &event)
{
    DoPhysicalDelete();
}
//deletes either the currently playing item or the selected item from the playlist
void MediaPlaylist::DoPhysicalDelete(bool currentFile)
{
    wxString itemname, path;

	//wxListItem object will hold some information about the item such as ID, data etc
    wxListItem item;

	//if the item being deleted is the currently playing file (which is always referenced by LastFileId) we
	//get the data associated with the LastFileId and delete it from the playlist and after that
    if(currentFile)
    {
         path = (*(wxString*)GetItemData(LastFileId));
         itemname = wxFileName(path).GetFullName();
    }
    else
    {
	/*
	if the item is not the currently playing file, we associate the wxListItem with the currently selected item  in the playlist
	*/
        GetSelectedItem(item);
        path = (*(wxString*)item.GetData());
        itemname = wxFileName(path).GetFullName();
    }

    int ans = wxMessageBox("This will physically delete the following file your computer\n"+itemname+"\nContinue?","prompt", wxYES_NO | wxICON_QUESTION);
    if(ans == wxYES)
    {
        if(wxRemoveFile(path))
        {
            currentFile ? DeleteItem(LastFileId) : DeleteItem(item);
            ArrangeQueue();
            if(currentFile || LastFileId == item.GetId())
            {
                if(GetItemCount() != 0)
                    ((MediaFrame *)parent)->DoChangeSong();
                else
                    //((MediaFrame *)parent)->media->Stop();
                    BASS_ChannelStop(((MediaFrame*)parent)->str);
            }
        }
        else
            wxMessageBox("File not found");
    }

}
//RAFS
