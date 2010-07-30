#include "configsettingsdialog.h"
#include "mcupluginmanager.h"

//(*InternalHeaders(ConfigSettingsDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(ConfigSettingsDialog)
const long ConfigSettingsDialog::ID_CUSTOMCONFIGPANEL = wxNewId();
const long ConfigSettingsDialog::ID_BUTTONOK = wxNewId();
const long ConfigSettingsDialog::ID_BUTTONCANCEL = wxNewId();
//*)

BEGIN_EVENT_TABLE(ConfigSettingsDialog,wxDialog)
	//(*EventTable(ConfigSettingsDialog)
	//*)
END_EVENT_TABLE()

ConfigSettingsDialog::ConfigSettingsDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(ConfigSettingsDialog)
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(474,473));
	SetMinSize(wxSize(-1,-1));
	FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
	CustomConfigPanel = new ConfigSettingsPanel(this);
	FlexGridSizer1->Add(CustomConfigPanel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	ButtonOk = new wxButton(this, ID_BUTTONOK, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONOK"));
	BoxSizer1->Add(ButtonOk, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonCancel = new wxButton(this, ID_BUTTONCANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONCANCEL"));
	BoxSizer1->Add(ButtonCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BUTTONOK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ConfigSettingsDialog::OnButtonOkClick);
	Connect(ID_BUTTONCANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ConfigSettingsDialog::OnButtonCancelClick);
	//*)
}

ConfigSettingsDialog::~ConfigSettingsDialog()
{
	//(*Destroy(ConfigSettingsDialog)
	//*)
}

void ConfigSettingsDialog::OnCustomConfigPanelPaint(wxPaintEvent& event)
{
}

void ConfigSettingsDialog::OnButtonOkClick(wxCommandEvent& event)
{
    mcuPluginManager::GetInstance()->ApplyConfigSettings();
    EndDialog(wxID_OK);
}

void ConfigSettingsDialog::OnButtonCancelClick(wxCommandEvent& event)
{
    EndDialog(wxID_CANCEL);
}
