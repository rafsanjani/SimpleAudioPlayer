#include "MyPanel.h"

//only processes three events cos the aim of deriving this class was just to enable dragging from the panel
BEGIN_EVENT_TABLE(MyPanel, wxPanel)
    EVT_LEFT_DOWN(MyPanel::OnLeftDown)
    EVT_LEFT_UP(MyPanel::OnLeftUp)
    EVT_MOTION(MyPanel::OnMouseMove)
END_EVENT_TABLE()

MyPanel::MyPanel(wxFrame *parent)
        :wxPanel(parent,wxID_ANY,wxDefaultPosition, wxDefaultSize, wxCLIP_CHILDREN)
{
    this->parent = parent;
}
//if left button is clicked, we capture the pointer and save the coordinates of the position where the click
//event occured (pos). also we save the coordinates of the frame's position on the screen into a variable(origin) and we calculate
//for the gradient so that in case user drags, the gradient can help us to know where the user is dragging to
void MyPanel::OnLeftDown(wxMouseEvent &event)
{
    CaptureMouse();
    wxPoint pos = parent->ClientToScreen(event.GetPosition());
    wxPoint origin = parent->GetPosition();
    int dx =  pos.x - origin.x;
    int dy = pos.y - origin.y;
    m_delta = wxPoint(dx, dy);
}

void MyPanel::OnLeftUp(wxMouseEvent &event)
{
    if (HasCapture())
    {
        ReleaseMouse();
    }
}
//if mouse is moving, we check to see whether the left is down and also whether the user is dragging,
//if all checks succeed, we get the position of the window in relation to the screen and move the frame
//accordingly by subtracting the gradient from the new position of the mouse
void MyPanel::OnMouseMove(wxMouseEvent &event)
{
    wxPoint pt = event.GetPosition();
    if (event.Dragging() && event.LeftIsDown())
    {
        wxPoint pos = parent->ClientToScreen(pt);
        parent->Move(wxPoint(pos.x - m_delta.x, pos.y - m_delta.y));
    }
}

MyPanel::~MyPanel()
{
}
//RAFS
