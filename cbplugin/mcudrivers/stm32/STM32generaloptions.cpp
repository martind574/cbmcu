#include "STM32generaloptions.h"

//(*InternalHeaders(STM32GeneralOptions)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(STM32GeneralOptions)
const long STM32GeneralOptions::ID_STATICTEXT1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(STM32GeneralOptions,wxPanel)
	//(*EventTable(STM32GeneralOptions)
	//*)
END_EVENT_TABLE()

STM32GeneralOptions::STM32GeneralOptions(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(STM32GeneralOptions)
	wxFlexGridSizer* FlexGridSizer1;
	
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("(Option bytes will go here)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	//*)
}

STM32GeneralOptions::~STM32GeneralOptions()
{
	//(*Destroy(STM32GeneralOptions)
	//*)
}

