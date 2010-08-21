#include "openocdset.h"

//(*InternalHeaders(OpenOCDSet)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(OpenOCDSet)
const long OpenOCDSet::ID_STATICTEXT1 = wxNewId();
const long OpenOCDSet::ID_TEXTCTRL_OPENOCDLOC = wxNewId();
const long OpenOCDSet::ID_BUTTON_SELOPENOCD = wxNewId();
const long OpenOCDSet::ID_STATICTEXT_TCLPORT = wxNewId();
const long OpenOCDSet::ID_TEXTCTRL1 = wxNewId();
const long OpenOCDSet::ID_STATICTEXT_TELNETPORT = wxNewId();
const long OpenOCDSet::ID_TEXTCTRL_TELNETPORT = wxNewId();
const long OpenOCDSet::ID_STATICTEXT_GDBPORT = wxNewId();
const long OpenOCDSet::ID_TEXTCTRL_GDBPORT = wxNewId();
//*)

BEGIN_EVENT_TABLE(OpenOCDSet,wxPanel)
	//(*EventTable(OpenOCDSet)
	//*)
END_EVENT_TABLE()

OpenOCDSet::OpenOCDSet(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(OpenOCDSet)
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxBoxSizer* BoxSizer1;
	wxStaticBoxSizer* StaticBoxSizerOpenOCDSettings;
	wxFlexGridSizer* FlexGridSizer1;
	wxBoxSizer* BoxSizer3;
	
	Create(parent, id, wxDefaultPosition, wxSize(163,128), wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticBoxSizerOpenOCDSettings = new wxStaticBoxSizer(wxVERTICAL, this, _("OpenOCD settings"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticTextOpenOCD = new wxStaticText(this, ID_STATICTEXT1, _("openocd.exe:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticTextOpenOCD, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlOpenOCDLoc = new wxTextCtrl(this, ID_TEXTCTRL_OPENOCDLOC, wxEmptyString, wxDefaultPosition, wxSize(230,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL_OPENOCDLOC"));
	FlexGridSizer1->Add(TextCtrlOpenOCDLoc, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonSelOpenOCD = new wxButton(this, ID_BUTTON_SELOPENOCD, _("Select..."), wxDefaultPosition, wxSize(55,23), 0, wxDefaultValidator, _T("ID_BUTTON_SELOPENOCD"));
	FlexGridSizer1->Add(ButtonSelOpenOCD, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizerOpenOCDSettings->Add(FlexGridSizer1, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	StaticTextTCLPort = new wxStaticText(this, ID_STATICTEXT_TCLPORT, _("TCL port:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_TCLPORT"));
	BoxSizer5->Add(StaticTextTCLPort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlTCLPort = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(75,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer5->Add(TextCtrlTCLPort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizerOpenOCDSettings->Add(BoxSizer5, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	StaticTextTelnetPort = new wxStaticText(this, ID_STATICTEXT_TELNETPORT, _("Telnet port:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_TELNETPORT"));
	BoxSizer4->Add(StaticTextTelnetPort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlTelnetPort = new wxTextCtrl(this, ID_TEXTCTRL_TELNETPORT, wxEmptyString, wxDefaultPosition, wxSize(75,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL_TELNETPORT"));
	BoxSizer4->Add(TextCtrlTelnetPort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizerOpenOCDSettings->Add(BoxSizer4, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticTextGDBPort = new wxStaticText(this, ID_STATICTEXT_GDBPORT, _("GDB port:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT_GDBPORT"));
	BoxSizer3->Add(StaticTextGDBPort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlGDBPort = new wxTextCtrl(this, ID_TEXTCTRL_GDBPORT, wxEmptyString, wxDefaultPosition, wxSize(75,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL_GDBPORT"));
	BoxSizer3->Add(TextCtrlGDBPort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizerOpenOCDSettings->Add(BoxSizer3, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticBoxSizerOpenOCDSettings->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(StaticBoxSizerOpenOCDSettings, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	BoxSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	FileDialogSelectLoc = new wxFileDialog(this, _("Find OpenOCD.exe"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
	BoxSizer1->SetSizeHints(this);
	
	Connect(ID_BUTTON_SELOPENOCD,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenOCDSet::OnButtonSelOpenOCDClick);
	//*)

	m_GDBPort = 0;
	m_TelnetPort = 0;
	m_TCLPort = 0;
}

OpenOCDSet::~OpenOCDSet()
{
	//(*Destroy(OpenOCDSet)
	//*)
}

void OpenOCDSet::OnButtonSelOpenOCDClick(wxCommandEvent& event)
{
    int nRet = FileDialogSelectLoc->ShowModal();
    if (nRet == wxID_OK) {
        TextCtrlOpenOCDLoc->SetValue(FileDialogSelectLoc->GetPath());
    }
}

void OpenOCDSet::LoadSettings(void)
{
    wxString str;

    TextCtrlOpenOCDLoc->SetValue(m_ProgramPath);

    str = wxString::Format(_T("%d"), m_GDBPort);
    TextCtrlGDBPort->SetValue(str);

    str = wxString::Format(_T("%d"), m_TelnetPort);
    TextCtrlTelnetPort->SetValue(str);

    str = wxString::Format(_T("%d"), m_TCLPort);
    TextCtrlTCLPort->SetValue(str);
}

void OpenOCDSet::SaveSettings(void)
{
    wxString str;

    m_ProgramPath = TextCtrlOpenOCDLoc->GetValue();

    str = TextCtrlGDBPort->GetValue();
    m_GDBPort = atoi(str.mb_str());

    str = TextCtrlTelnetPort->GetValue();
    m_TelnetPort = atoi(str.mb_str());

    str = TextCtrlTCLPort->GetValue();
    m_TCLPort = atoi(str.mb_str());
}
