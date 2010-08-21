#include "devparportadvopts.h"

//(*InternalHeaders(DevParportAdvOpts)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(DevParportAdvOpts)
const long DevParportAdvOpts::ID_STATICTEXT1 = wxNewId();
const long DevParportAdvOpts::ID_CHOICE_PARPORT = wxNewId();
//*)

BEGIN_EVENT_TABLE(DevParportAdvOpts,wxDialog)
	//(*EventTable(DevParportAdvOpts)
	//*)
END_EVENT_TABLE()

DevParportAdvOpts::DevParportAdvOpts(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(DevParportAdvOpts)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer3;

	Create(parent, id, _("Parallel port address"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(255,183));
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(2, 2, 0, 0);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Device:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ChoicePort = new wxChoice(this, ID_CHOICE_PARPORT, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_PARPORT"));
	BoxSizer1->Add(ChoicePort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	ButtonOK = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	ButtonOK->SetDefault();
	BoxSizer3->Add(ButtonOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	BoxSizer3->Add(ButtonCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);
	//*)

	ChoicePort->Append(_("LPT1"));
	ChoicePort->Append(_("LPT2"));
	ChoicePort->Append(_("LPT3"));
}

DevParportAdvOpts::~DevParportAdvOpts()
{
	//(*Destroy(DevParportAdvOpts)
	//*)
}

void DevParportAdvOpts::EndModal(int retCode)
{
    if (retCode == wxID_OK) {
        m_Port = ChoicePort->GetStringSelection();
    }
    wxDialog::EndModal(retCode);
}

void DevParportAdvOpts::InitDialog(void)
{
    if (ChoicePort->SetStringSelection(m_Port) < 0)
        ChoicePort->SetSelection(0);
}
