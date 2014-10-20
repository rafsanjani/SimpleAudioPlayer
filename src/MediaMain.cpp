#include <wx/wx.h>
#include "MediaMain.h"
#include "MediaApp.h"
IMPLEMENT_APP(MyApp)

BEGIN_EVENT_TABLE(MyApp, wxApp)
    EVT_HIBERNATE(MyApp::OnHibernate)
    EVT_END_SESSION(MyApp::OnEndSession)
END_EVENT_TABLE()


void MyApp::OnInitCmdLine(wxCmdLineParser& parser)
{
wxApp::OnInitCmdLine(parser);

    parser.AddParam("input files",
                    wxCMD_LINE_VAL_STRING,
                    wxCMD_LINE_PARAM_OPTIONAL | wxCMD_LINE_PARAM_MULTIPLE);

}

bool MyApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    if ( !wxApp::OnCmdLineParsed(parser) )
        return false;

    for (size_t paramNr=0; paramNr < parser.GetParamCount(); ++paramNr)
        m_params.push_back(parser.GetParam(paramNr));

    return true;
}

bool MyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    SetVendorName("RAFSANJANI");
    //SetAppName("SIMPLE AUDIO PLAYER");
    SetAppName(AppName);

    /*
    uncomment these lines to disable multiple instances of the app
    const wxString name = wxString::Format("MyApp-%s", wxGetUserId().c_str());
    m_checker = new wxSingleInstanceChecker(name);

    if(m_checker->IsAnotherRunning()){
        //do something if program is already running.
        //shall be removing this function soon.

    return false;
    }
    */
    MediaFrame *frame = new MediaFrame(NULL, AppName, wxDefaultPosition,
                                wxSize(390,400),wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION);

    wxPoint pos = frame->screenPosition;

    frame->SetIcon(wxICON(aaaaa));
    frame->Move(pos);
    frame->ShowWithEffect(wxSHOW_EFFECT_BLEND, 800);
	frame->Refresh();
    return true;
}

//for some unknown reason, these events are not properly handled as expected
void MyApp::OnHibernate(wxActivateEvent &event)
{
	wxMessageBox("I am hibernating.......");
}

void MyApp::OnEndSession(wxCloseEvent &event)
{
    if(event.GetLoggingOff())
    {
		wxMessageBox("I am just logging off");
    }
		wxMessageBox("I am really shutting down");
}
//RAFS
