#include "openocdintloc.h"

//(*InternalHeaders(openocdintloc)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(openocdintloc)
const long openocdintloc::ID_STATICBOX1 = wxNewId();
const long openocdintloc::ID_STATICTEXT1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(openocdintloc,wxPanel)
	//(*EventTable(openocdintloc)
	//*)
END_EVENT_TABLE()

openocdintloc::openocdintloc(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(openocdintloc)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer3;
	
	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer3->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("Label"), wxDefaultPosition, wxSize(158,151), 0, _T("ID_STATICBOX1"));
	BoxSizer3->Add(StaticBox1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("openocd.exe location:"), wxDefaultPosition, wxSize(106,13), 0, _T("ID_STATICTEXT1"));
	BoxSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)
}

openocdintloc::~openocdintloc()
{
	//(*Destroy(openocdintloc)
	//*)
}

