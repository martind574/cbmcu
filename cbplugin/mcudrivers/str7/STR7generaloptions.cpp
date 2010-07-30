#include "STR7generaloptions.h"

//(*InternalHeaders(STR7GeneralOptions)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(STR7GeneralOptions)
const long STR7GeneralOptions::ID_CHECKBOXUNPROTECT = wxNewId();
//*)

BEGIN_EVENT_TABLE(STR7GeneralOptions,wxPanel)
	//(*EventTable(STR7GeneralOptions)
	//*)
END_EVENT_TABLE()

STR7GeneralOptions::STR7GeneralOptions(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(STR7GeneralOptions)
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Flash options"));
	CheckBoxUnprotect = new wxCheckBox(this, ID_CHECKBOXUNPROTECT, _("Un-protect flash at start"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOXUNPROTECT"));
	CheckBoxUnprotect->SetValue(false);
	StaticBoxSizer1->Add(CheckBoxUnprotect, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	//*)
}

STR7GeneralOptions::~STR7GeneralOptions()
{
	//(*Destroy(STR7GeneralOptions)
	//*)
}

bool STR7GeneralOptions::SaveSettings(void)
{
    m_UnprotectFlash = CheckBoxUnprotect->GetValue();
    return true;
}

void STR7GeneralOptions::LoadSettings(void)
{
    if (m_UnprotectFlash == true)
        CheckBoxUnprotect->SetValue(true);
    else
        CheckBoxUnprotect->SetValue(false);
}


