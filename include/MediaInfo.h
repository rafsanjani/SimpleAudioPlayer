///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MEDIAINFO_H__
#define __MEDIAINFO_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
//#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
//#include <wx/string.h>
#include <wx/textctrl.h>
//#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/statline.h>
//#include <wx/panel.h>
#include <wx/hyperlink.h>
//#include <wx/button.h>
//#include <wx/dialog.h>
#include <wx/wx.h>
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MediaInfo
///////////////////////////////////////////////////////////////////////////////
class MediaInfo : public wxDialog
{
	private:

	protected:
		wxStaticBitmap* m_bitmap2;
		wxPanel* mainPanel;
		wxTextCtrl* filePath;
		wxStaticText* titleTag;
		wxStaticText* artistValue;
		wxStaticText* artistTag;
		wxStaticText* titleValue;
		wxStaticText* albumTag;
		wxStaticText* albumValue;
		wxStaticText* genreTag;
		wxStaticText* genreValue;
		wxStaticText* yearTag;
		wxStaticText* yearValue;
		wxStaticLine* m_staticline3;
		wxStaticText* formatTag;
		wxStaticText* formatValue;
		wxStaticText* durationTag;
		wxStaticText* durationValue;
		wxStaticText* qualityTag;
		wxStaticText* qualityValue;
		wxStaticText* sizeTag;
		wxStaticText* sizeValue;
		wxPanel* albumArtPanel;
		wxStaticBitmap* albumArt;
		wxHyperlinkCtrl* homePageUrl;
		wxButton* closeButton;

		void OnEnterWindow( wxMouseEvent& event );
		void OnLeaveWindow( wxMouseEvent& event );
		void OnLeftDown( wxMouseEvent& event );
		void OnLeftUp( wxMouseEvent& event );
		void OnLinkHover( wxMouseEvent& event );
		void OnLinkHoverEnd( wxMouseEvent& event );

		void OnCloseButton(wxCommandEvent &event);


	public:
	    void SetFilePath(wxString path);
	    void SetDuration(wxString duration);
	    void SetTitle(wxString title);
	    void SetArtist(wxString artist);
	    void SetAlbum(wxString album);
	    void SetGenre(wxString genre);
	    void SetFormat(wxString format);
	    void SetYear(wxString year);
	    void SetQuality(wxString samplerate, wxString bitrate, wxString channel);
	    void SetSize(wxString m_size);
	    void SetAlbumArt(wxBitmap albumart);


		MediaInfo( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Tag Viewer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 520,450 ), long style = wxDEFAULT_DIALOG_STYLE );
		~MediaInfo();

};

#endif //__MEDIAINFO_H__

