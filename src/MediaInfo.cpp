///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Mediainfo.h"

///////////////////////////////////////////////////////////////////////////

MediaInfo::MediaInfo( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
    wxInitAllImageHandlers();
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	m_bitmap2 = new wxStaticBitmap( this, wxID_ANY, wxBITMAP_PNG(HEADER2) , wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_bitmap2, 0, 0, 5 );

	mainPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
	mainPanel->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer( wxVERTICAL );

	filePath = new wxTextCtrl( mainPanel, wxID_ANY, wxT("Path to media file"), wxDefaultPosition, wxSize( 500,25 ), wxTE_READONLY );
	bSizer55->Add( filePath, 1, wxALL, 5 );

	wxBoxSizer* bSizer191;
	bSizer191 = new wxBoxSizer( wxHORIZONTAL );

	titleTag = new wxStaticText( mainPanel, wxID_ANY, wxT("Title"), wxDefaultPosition, wxDefaultSize, 0 );
	titleTag->Wrap( -1 );
	titleTag->SetFont( wxFont( 10, 70, 90, 92, false, wxT("Arial") ) );

	bSizer191->Add( titleTag, 0, wxALL, 2 );


	bSizer191->Add( 0, 0, 0, wxLEFT, 85 );

	titleValue = new wxStaticText( mainPanel, wxID_ANY, wxT("sdasdasasdasdasdasasdasdas"), wxPoint( -1,-1 ), wxSize( 300,-1 ), 0 );
	titleValue->Wrap( -1 );
	bSizer191->Add( titleValue, 2, wxALL, 5 );


	bSizer55->Add( bSizer191, 1, 0, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer171;
	bSizer171 = new wxBoxSizer( wxHORIZONTAL );

	artistTag = new wxStaticText( mainPanel, wxID_ANY, wxT("Artist"), wxDefaultPosition, wxDefaultSize, 0 );
	artistTag->Wrap( -1 );
	artistTag->SetFont( wxFont( 10, 74, 90, 92, false, wxT("Arial") ) );

	bSizer171->Add( artistTag, 1, wxALL, 2 );

	artistValue = new wxStaticText( mainPanel, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	artistValue->Wrap( -1 );
	bSizer171->Add( artistValue, 1, wxALL, 5 );


	bSizer17->Add( bSizer171, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer192;
	bSizer192 = new wxBoxSizer( wxHORIZONTAL );

	albumTag = new wxStaticText( mainPanel, wxID_ANY, wxT("Album"), wxDefaultPosition, wxDefaultSize, 0 );
	albumTag->Wrap( -1 );
	albumTag->SetFont( wxFont( 10, 74, 90, 92, false, wxT("Arial") ) );

	bSizer192->Add( albumTag, 1, wxALL, 2 );

	albumValue = new wxStaticText( mainPanel, wxID_ANY, wxT("The Leak"), wxDefaultPosition, wxDefaultSize, 0 );
	albumValue->Wrap( -1 );
	bSizer192->Add( albumValue, 1, wxALL, 2 );


	bSizer17->Add( bSizer192, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer193;
	bSizer193 = new wxBoxSizer( wxHORIZONTAL );

	genreTag = new wxStaticText( mainPanel, wxID_ANY, wxT("Genre"), wxDefaultPosition, wxDefaultSize, 0 );
	genreTag->Wrap( -1 );
	genreTag->SetFont( wxFont( 10, 74, 90, 92, false, wxT("Arial") ) );

	bSizer193->Add( genreTag, 1, wxALL, 2 );

	genreValue = new wxStaticText( mainPanel, wxID_ANY, wxT("Hip Hop"), wxDefaultPosition, wxDefaultSize, 0 );
	genreValue->Wrap( -1 );
	bSizer193->Add( genreValue, 1, wxALL, 2 );


	bSizer17->Add( bSizer193, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer194;
	bSizer194 = new wxBoxSizer( wxHORIZONTAL );

	yearTag = new wxStaticText( mainPanel, wxID_ANY, wxT("Year"), wxDefaultPosition, wxDefaultSize, 0 );
	yearTag->Wrap( -1 );
	yearTag->SetFont( wxFont( 10, 74, 90, 92, false, wxT("Arial") ) );

	bSizer194->Add( yearTag, 1, wxALL, 2 );

	yearValue = new wxStaticText( mainPanel, wxID_ANY, wxT("2014"), wxDefaultPosition, wxDefaultSize, 0 );
	yearValue->Wrap( -1 );
	bSizer194->Add( yearValue, 1, wxALL, 2 );


	bSizer17->Add( bSizer194, 1, wxEXPAND, 5 );

	m_staticline3 = new wxStaticLine( mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer17->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer195;
	bSizer195 = new wxBoxSizer( wxHORIZONTAL );

	formatTag = new wxStaticText( mainPanel, wxID_ANY, wxT("Format"), wxDefaultPosition, wxDefaultSize, 0 );
	formatTag->Wrap( -1 );
	formatTag->SetFont( wxFont( 10, 74, 90, 92, false, wxT("Arial") ) );

	bSizer195->Add( formatTag, 1, wxALL, 2 );

	formatValue = new wxStaticText( mainPanel, wxID_ANY, wxT("MP3"), wxDefaultPosition, wxDefaultSize, 0 );
	formatValue->Wrap( -1 );
	bSizer195->Add( formatValue, 1, wxALL, 2 );


	bSizer17->Add( bSizer195, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer196;
	bSizer196 = new wxBoxSizer( wxHORIZONTAL );

	durationTag = new wxStaticText( mainPanel, wxID_ANY, wxT("Duration"), wxDefaultPosition, wxDefaultSize, 0 );
	durationTag->Wrap( -1 );
	durationTag->SetFont( wxFont( 10, 74, 90, 92, false, wxT("Arial") ) );

	bSizer196->Add( durationTag, 1, wxALL, 2 );

	durationValue = new wxStaticText( mainPanel, wxID_ANY, wxT("3:25"), wxDefaultPosition, wxDefaultSize, 0 );
	durationValue->Wrap( -1 );
	bSizer196->Add( durationValue, 1, wxALL, 2 );


	bSizer17->Add( bSizer196, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer197;
	bSizer197 = new wxBoxSizer( wxHORIZONTAL );

	qualityTag = new wxStaticText( mainPanel, wxID_ANY, wxT("Quality"), wxDefaultPosition, wxDefaultSize, 0 );
	qualityTag->Wrap( -1 );
	qualityTag->SetFont( wxFont( 10, 74, 90, 92, false, wxT("Arial") ) );

	bSizer197->Add( qualityTag, 1, wxALL, 2 );

	qualityValue = new wxStaticText( mainPanel, wxID_ANY, wxT("4400Hz, 256bkps, 16"), wxDefaultPosition, wxDefaultSize, 0 );
	qualityValue->Wrap( -1 );
	bSizer197->Add( qualityValue, 1, wxALL, 2 );


	bSizer17->Add( bSizer197, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer198;
	bSizer198 = new wxBoxSizer( wxHORIZONTAL );

	sizeTag = new wxStaticText( mainPanel, wxID_ANY, wxT("Size"), wxDefaultPosition, wxDefaultSize, 0 );
	sizeTag->Wrap( -1 );
	sizeTag->SetFont( wxFont( 10, 74, 90, 92, false, wxT("Arial") ) );

	bSizer198->Add( sizeTag, 1, wxALL, 2 );

	sizeValue = new wxStaticText( mainPanel, wxID_ANY, wxT("3.45MB"), wxDefaultPosition, wxDefaultSize, 0 );
	sizeValue->Wrap( -1 );
	bSizer198->Add( sizeValue, 1, wxALL, 2 );


	bSizer17->Add( bSizer198, 1, wxEXPAND, 5 );


	bSizer16->Add( bSizer17, 1, wxEXPAND, 5 );

	albumArtPanel = new wxPanel( mainPanel, wxID_ANY, wxDefaultPosition, wxSize( 20,170 ), wxDOUBLE_BORDER|wxTAB_TRAVERSAL );
	albumArtPanel->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BACKGROUND ) );
	albumArtPanel->SetMinSize( wxSize( 20,170 ) );

	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxVERTICAL );

	albumArt = new wxStaticBitmap( albumArtPanel, wxID_ANY, wxBITMAP_PNG(ALBUMART), wxDefaultPosition, wxDefaultSize, 0 );
	albumArt->SetMinSize( wxSize( 200,400 ) );

	bSizer49->Add( albumArt, 1, wxALL|wxEXPAND, 5 );


	albumArtPanel->SetSizer( bSizer49 );
	albumArtPanel->Layout();
	bSizer16->Add( albumArtPanel, 1, wxALIGN_RIGHT|wxALL, 2 );


	bSizer13->Add( bSizer16, 1, wxEXPAND, 5 );


	bSizer55->Add( bSizer13, 1, wxEXPAND, 5 );


	mainPanel->SetSizer( bSizer55 );
	mainPanel->Layout();
	bSizer55->Fit( mainPanel );
	bSizer12->Add( mainPanel, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer( wxHORIZONTAL );

	homePageUrl = new wxHyperlinkCtrl( this, wxID_ANY, wxT("http://foreverraf.tk/"), wxT("http://www.foreverraf.tk/"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );

	homePageUrl->SetHoverColour(wxColour("RED"));
	homePageUrl->SetNormalColour(wxColour("BLUE") );
	homePageUrl->SetVisitedColour(wxColour("PINK") );
	bSizer59->Add( homePageUrl, 0, wxALL, 5 );


	bSizer59->Add( 0, 0, 1, wxEXPAND, 5 );

	closeButton = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer59->Add( closeButton, 0, wxALIGN_RIGHT|wxALL, 5 );

	closeButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MediaInfo::OnCloseButton), this, NULL);


	bSizer12->Add( bSizer59, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer12 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	albumArt->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( MediaInfo::OnEnterWindow ), NULL, this );
	albumArt->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( MediaInfo::OnLeaveWindow ), NULL, this );
	albumArt->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( MediaInfo::OnLeftDown ), NULL, this );
	albumArt->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( MediaInfo::OnLeftUp ), NULL, this );
	homePageUrl->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( MediaInfo::OnLinkHover ), NULL, this );
	homePageUrl->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( MediaInfo::OnLinkHoverEnd ), NULL, this );
}

void MediaInfo::SetFilePath(wxString path)
{
    filePath->SetValue(path);
}
void MediaInfo::SetDuration(wxString duration)
{
    durationValue->SetLabel(duration);
}

void MediaInfo::SetArtist(wxString artist)
{
    artistValue->SetLabel(artist);
}

void MediaInfo::SetTitle(wxString title)
{
    titleValue->SetLabel(title);
}
void MediaInfo::SetAlbum(wxString album)
{
    albumValue->SetLabel(album);
}

void MediaInfo::SetGenre(wxString genre)
{
    genreValue->SetLabel(genre);
}

void MediaInfo::SetFormat(wxString format)
{
    formatValue->SetLabel(format);
}

void MediaInfo::SetYear(wxString year)
{
    yearValue->SetLabel(year);
}

void MediaInfo::SetQuality(wxString samplerate, wxString bitrate, wxString channel)
{
    qualityValue->SetLabel(samplerate+", "+bitrate+", "+channel);
}

void MediaInfo::SetSize( wxString m_size)
{
    sizeValue->SetLabel(m_size);
}

void MediaInfo::SetAlbumArt(wxBitmap albumart)
{
    albumArt->SetBitmap(albumart);
}




void MediaInfo::OnLeftDown(wxMouseEvent &event)
{

}

void MediaInfo::OnLeftUp(wxMouseEvent &event)
{

}

void MediaInfo::OnLinkHover(wxMouseEvent &event)
{
    homePageUrl->SetFont(wxFont( 9, 70, 90, 90, false, wxT("Segoe Print") ) );
    homePageUrl->SetLabel("Home Page");
    homePageUrl->Refresh();
}


void MediaInfo::OnLinkHoverEnd(wxMouseEvent &event)
{
    //homePageUrl->SetFont(wxFont(9, 70, 90, 90, false, "Arial"));
    //homePageUrl->SetLabel("http://www.foreverraf.tk/");
    //homePageUrl->Refresh();
}

void MediaInfo::OnEnterWindow(wxMouseEvent &event)
{
   //wxMessageBox("in window");
   albumArtPanel->SetBackgroundColour(wxColour("RED"));
   albumArtPanel->Refresh();
}

void MediaInfo::OnLeaveWindow(wxMouseEvent &event)
{
   // wxMessageBox("out of window");
    albumArtPanel->SetBackgroundColour(wxColour("BLACK"));
    albumArtPanel->Refresh();
}

void MediaInfo::OnCloseButton(wxCommandEvent &event)
{
    Destroy();
}

MediaInfo::~MediaInfo()
{
	// Disconnect Events
	albumArt->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( MediaInfo::OnEnterWindow ), NULL, this );
	albumArt->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( MediaInfo::OnLeaveWindow ), NULL, this );
	albumArt->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( MediaInfo::OnLeftDown ), NULL, this );
	albumArt->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( MediaInfo::OnLeftUp ), NULL, this );
	homePageUrl->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( MediaInfo::OnLinkHover ), NULL, this );
	homePageUrl->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( MediaInfo::OnLinkHoverEnd ), NULL, this );
}


