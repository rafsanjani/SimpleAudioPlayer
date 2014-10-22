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
#include <id3v2tag.h>
#include <mpegfile.h>
#include <id3v2frame.h>
#include <id3v2header.h>
#include <attachedpictureframe.h>
#include <iostream>
#include <fstream>
#include <string>

using std::ios;
using std::fstream;
using std::ofstream;
#include <fileref.h>
//using namespace TagLib;

class TagReader
{
    public:
        TagReader(wxString file);

        bool HasTags();
        void Free();
        wxString GetTitle() ;
        wxString GetArtist();
        wxString GetTime();
        wxString GetYear();
        wxString GetGenre();
        wxString GetComment();
        wxString GetChannel();
        wxString GetAlbum();
        wxString GetBitrate();
        wxString GetSamplerate();
        wxBitmap GetAlbumArt();
        ~TagReader();

    private:
        bool ProcessAlbumArt();
        bool tagsFound;
        TagLib::FileRef *myFile;
        TagLib::Tag *tag;
        TagLib::ID3v2::Tag *id3v2;
        TagLib::AudioProperties *audioProperties;

        wxString file, title, artist, time, year,
        channel, genre, comment, album, bitrate, samplerate;

        wxString ToWxString(TagLib::String file);
        TagLib::String FormatSeconds(int seconds);

};
#endif

