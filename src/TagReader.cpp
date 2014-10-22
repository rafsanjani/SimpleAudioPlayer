#include "TagReader.h"
#include <iostream>
#include "fstream"

using std::ios;
using std::fstream;

TagReader::TagReader(wxString inFile)
{
    //wxInitAllImageHandlers();
    file = inFile;
    myFile = new TagLib::FileRef(inFile.t_str());

    if(HasTags())
    {
        tag = myFile->tag();
        audioProperties = myFile->audioProperties();
    }

}

bool TagReader::HasTags()
{
    tagsFound = (!myFile->isNull() && myFile->tag());
    return tagsFound;
}

wxString TagReader::GetAlbum()
{
    album = tagsFound ? ToWxString(tag->album()) : " ";
    return album;
}

wxString TagReader::GetArtist()
{
    artist = tagsFound ? ToWxString(tag->artist()) :  " ";
    return artist;
}

wxString TagReader::GetBitrate()
{
    bitrate = tagsFound ? wxString::Format("%dkbps", audioProperties->bitrate()) : " ";
    return bitrate;
}

wxString TagReader::GetChannel()
{
    channel = tagsFound ? wxString::Format("%d", audioProperties->channels()) : " ";
    return channel;
}
wxString TagReader::GetComment()
{
    comment = tagsFound ? ToWxString(tag->comment()) : " ";
    return comment;
}
wxString TagReader::GetGenre()
{
    genre = tagsFound ? ToWxString(tag->genre()) : " ";
    return genre;
}

wxString TagReader::GetSamplerate()
{
    samplerate = tagsFound ? wxString::Format("%dHz", audioProperties->sampleRate()) : " ";
    return samplerate;
}

wxString TagReader::GetTime()
{
    int seconds = audioProperties->length() % 60;
    int minutes = (audioProperties->length() - seconds) / 60;
    TagLib::String temp = FormatSeconds(seconds);

    time = wxString::Format("%2i:"+ToWxString(temp), minutes);
    return time;
}

wxString TagReader::GetTitle()
{
    tagsFound ? title = ToWxString(tag->title()) : title = " ";
    return title;
}

wxString TagReader::GetYear()
{
    int year_int = tag->year();
    year = tagsFound ? wxString::Format("%d", year_int) : " ";
    return year;
}

//method for converting from Taglib::String to wxString format
wxString TagReader::ToWxString(TagLib::String file)
{
    std::string temp = file.toCString(true);
    wxString output(temp.c_str(), wxConvUTF8);
    return output;
}

TagLib::String TagReader::FormatSeconds(int seconds)
{
    char secondsString[3];
    sprintf(secondsString, "%02i", seconds);
    return secondsString;
}

//obtained from:
//http://rajeevandlinux.wordpress.com/2012/04/24/extract-album-art-from-mp3-files-using-taglib-in-c/
bool TagReader::ProcessAlbumArt()
{
  delete myFile;
  const char *IdPicture = "APIC";

  TagLib::MPEG::File mpegFile(file.t_str());
  TagLib::ID3v2::Tag *id3v2tag = mpegFile.ID3v2Tag();
  TagLib::ID3v2::FrameList Frame ;
  TagLib::ID3v2::AttachedPictureFrame *PicFrame ;
  char *SrcImage ;
  unsigned long Size ;

  if ( id3v2tag )
  {
    std::fstream outFile("AlbumArt.png", ios::out | ios::binary);
    Frame = id3v2tag->frameListMap()[IdPicture] ;
    if (!Frame.isEmpty() )
    {
      for(TagLib::ID3v2::FrameList::ConstIterator it = Frame.begin(); it != Frame.end(); ++it)
      {
        PicFrame = (TagLib::ID3v2::AttachedPictureFrame *)(*it) ;
        {
          Size = PicFrame->picture().size() ;

          SrcImage = new char[Size];

          if ( SrcImage )
          {
            memcpy ( SrcImage, PicFrame->picture().data(), Size ) ;

            outFile.write(SrcImage, Size);

            outFile.close();
            delete SrcImage;
            return true;
          }

        }
      }
    }
  }
     return false;
}
wxBitmap TagReader::GetAlbumArt()
{
    wxBitmap bmp;

    if(ProcessAlbumArt()){
        bmp = wxBitmap( wxT("AlbumArt.png"), wxBITMAP_TYPE_ANY);
        return bmp;
    }
    else
        bmp = wxBitmap( wxT("NoAlbumArt.png"), wxBITMAP_TYPE_ANY);

    return bmp;
}

void TagReader::Free()
{
     //delete myFile;
}

TagReader::~TagReader()
{
    delete myFile;
}
