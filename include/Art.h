#ifndef ART_H_INCLUDED
#define ART_H_INCLUDED

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

namespace Art
{
    bool ProcessAlbumArt(wxString inFile)
    {
      const char *IdPicture = "APIC";
      wxMessageBox("trying to load file: \""+ inFile+"\"");
      TagLib::MPEG::File mpegFile(inFile.t_str());
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
    wxBitmap GetAlbumArt(wxString inFile)
    {
        wxBitmap bmp;

        if(ProcessAlbumArt(inFile)){
            bmp = wxBitmap( wxT("AlbumArt.png"), wxBITMAP_TYPE_ANY);
            return bmp;
        }
        else
            bmp = wxBitmap( wxT("NoAlbumArt.png"), wxBITMAP_TYPE_ANY);

        return bmp;
    }

}


#endif // ART_H_INCLUDED
