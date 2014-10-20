#include "TagReader.h"

TagReader::TagReader(const wxString &file)
{
    myFile = new TagLib::FileRef(file.t_str());

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
    bitrate = tagsFound ? wxString::Format("%d", audioProperties->bitrate()) : " ";
    return bitrate;
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
    samplerate = tagsFound ? wxString::Format("%d,", audioProperties->sampleRate()) : " ";
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

TagReader::~TagReader()
{
    delete myFile;
}