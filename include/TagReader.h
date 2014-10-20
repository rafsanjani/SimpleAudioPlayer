#ifndef TAGREADER_H
#define TAGREADER_H

/* TagReader.h
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
#include <wx/wx.h>
#include <tag.h>
#include <fileref.h>
//using namespace TagLib;

class TagReader
{
    public:
        TagReader(const wxString &file);

        bool HasTags();
        wxString GetTitle() ;
        wxString GetArtist();
        wxString GetTime();
        wxString GetYear();
        wxString GetGenre();
        wxString GetComment();
        wxString GetAlbum();
        wxString GetBitrate();
        wxString GetSamplerate();
        ~TagReader();

    private:
        bool tagsFound;
        TagLib::FileRef *myFile;
        TagLib::Tag *tag;
        TagLib::AudioProperties *audioProperties;

        wxString title, artist, time, year, genre, comment, album, bitrate, samplerate;

        wxString ToWxString(TagLib::String file);
        TagLib::String FormatSeconds(int seconds);

};
#endif

