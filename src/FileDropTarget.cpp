#include "FileDropTarget.h"
#include <sstream>
//file drop target for playlist
FileDropTarget::FileDropTarget(MediaPlaylist &m_listCtrl)
    :m_list(m_listCtrl)
{
}
//if a file is dropped onto the playlist from explorer window or from any other data source, we process the file
//and add it to the playlist. Open all subfolders and add process files in them too
bool FileDropTarget::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString &files)
{
    wxArrayString dirFiles;
    wxDir myDir;
    int unsupportedFiles = 0;
    for (size_t i = 0; i < files.GetCount(); ++i){
        if(myDir.Exists(files[i])){
            myDir.Open(files[i]);
            size_t itemCount = myDir.GetAllFiles(files[i], &dirFiles);
            for(size_t n = 0; n < itemCount; n++){
                if(IsFormatSupported(dirFiles[n])){
                    m_list.AddToPlayList(dirFiles[n]);
                }else{
                        unsupportedFiles++;
                    }
                }
           }
           else{
               if(IsFormatSupported(files[i])){
                  m_list.AddToPlayList(files[i]);
                  } else {
                    unsupportedFiles++;
                  }
           }
        }
    if(unsupportedFiles != 0)
        wxMessageBox(wxString::Format("%d Files couldn't be added\nReason: Unsupported Format",unsupportedFiles));
    return true;
}
//checks whether the dropped file is in a supported format before adding to the playlist. if check fails, user
//is presented with an error message showing the number of unsupported files
bool FileDropTarget::IsFormatSupported(wxString fileName)
{
    if(wxFileName(fileName).GetExt() == "mp3"|| wxFileName(fileName).GetExt() == "wma"|| wxFileName(fileName).GetExt() == "ogg"||
       wxFileName(fileName).GetExt() == "wav")
        return true;

    return false;
}
//RAFS

