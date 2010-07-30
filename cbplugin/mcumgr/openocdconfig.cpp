
#include "openocdconfig.h"

//(*InternalHeaders(OpenOCDConfig)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(OpenOCDConfig)
const long OpenOCDConfig::ID_STATICTEXT6 = wxNewId();
const long OpenOCDConfig::ID_TEXTCTRLPROGRAMLOCATION = wxNewId();
const long OpenOCDConfig::ID_BUTTON2 = wxNewId();
const long OpenOCDConfig::ID_STATICTEXT7 = wxNewId();
const long OpenOCDConfig::ID_TEXTCTRLGDBPORT = wxNewId();
const long OpenOCDConfig::ID_STATICTEXT5 = wxNewId();
const long OpenOCDConfig::ID_TEXTCTRLTELNETPORT = wxNewId();
const long OpenOCDConfig::ID_STATICTEXT9 = wxNewId();
const long OpenOCDConfig::ID_TEXTCTRLTCLPORT = wxNewId();
const long OpenOCDConfig::ID_STATICTEXT1 = wxNewId();
const long OpenOCDConfig::ID_CHOICEDEBUGDEVICE = wxNewId();
const long OpenOCDConfig::ID_STATICTEXT8 = wxNewId();
const long OpenOCDConfig::ID_CHOICEOPTION = wxNewId();
const long OpenOCDConfig::ID_STATICTEXT2 = wxNewId();
const long OpenOCDConfig::ID_CHOICEPORT = wxNewId();
const long OpenOCDConfig::ID_STATICTEXT3 = wxNewId();
const long OpenOCDConfig::ID_CHOICESPEED = wxNewId();
const long OpenOCDConfig::ID_STATICTEXT4 = wxNewId();
const long OpenOCDConfig::ID_TEXTCTRLCONFIGFILE = wxNewId();
const long OpenOCDConfig::ID_CHECKBOX1 = wxNewId();
//*)

const wxChar *OpenOCD_ft2232[] = {
    _T("usbjtag"),
    _T("jtagkey"),
    _T("signalyzer"),
    _T("olimex-jtag"),
    _T("m5960"),
    _T("evb_lm3s811"),
    _T("comstick"),
    _T("stm32stick"),
    _T("flyswatter"),
    _T("turtelizer2"),
    _T("oocdlink"),
    _T("axm0432")
};

const wxChar *OpenOCD_parport[] = {
    _T("wiggler"),
    _T("wiggler2"),
    _T("wiggler_ntrst_inverted"),
    _T("old_amt_wiggler"),
    _T("chameleon"),
    _T("dlc5"),
    _T("triton"),
    _T("flashlink"),
    _T("arm-jtag"),
    _T("altium")
};

OpenOCDDevs g_OpenOCDDevs[] = {
    {_T("parport"), OpenOCD_parport, 10},
    {_T("amt_jtagaccel"), NULL, 0},
    {_T("ft2232"), OpenOCD_ft2232, 12},
    {_T("ep93xx"), NULL, 0},
    {_T("presto"), NULL, 0},
    {_T("usbprog"), NULL, 0},
    {_T("gw16012"), NULL, 0},
    {_T("jlink"), NULL, 0},
    {_T("rlink"), NULL, 0},
    {_T("vsllink"), NULL, 0}
};


BEGIN_EVENT_TABLE(OpenOCDConfig,wxPanel)
	//(*EventTable(OpenOCDConfig)
	//*)
END_EVENT_TABLE()

OpenOCDConfig::OpenOCDConfig(wxWindow* parent):
    //m_Device(0),
    m_Speed(_("0")),
    m_GDBPort(2000),
    m_ConfigFile(_T("openocd.cfg")),
    m_Auto(true),
    m_TelnetPort(4444),
    m_TCLPort(6666),
    m_ProgramPath(_T(""))
{
	//(*Initialize(OpenOCDConfig)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer9;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer7;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxGridSizer* GridSizer1;
	wxFlexGridSizer* FlexGridSizer8;
	wxFlexGridSizer* FlexGridSizer6;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer11;
	
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(340,315), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	GridSizer1 = new wxGridSizer(2, 1, 0, 0);
	FlexGridSizer8 = new wxFlexGridSizer(2, 1, 0, 0);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxVERTICAL, this, _("Program location"));
	FlexGridSizer7 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("openocd.exe:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer7->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlProgramPath = new wxTextCtrl(this, ID_TEXTCTRLPROGRAMLOCATION, _("Text"), wxDefaultPosition, wxSize(244,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLPROGRAMLOCATION"));
	FlexGridSizer7->Add(TextCtrlProgramPath, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(this, ID_BUTTON2, _("Select..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer7->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer9 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("GDB Port:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer9->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlGDBPort = new wxTextCtrl(this, ID_TEXTCTRLGDBPORT, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRLGDBPORT"));
	FlexGridSizer9->Add(TextCtrlGDBPort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer9, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Telnet port:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer6->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlTelnetPort = new wxTextCtrl(this, ID_TEXTCTRLTELNETPORT, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRLTELNETPORT"));
	FlexGridSizer6->Add(TextCtrlTelnetPort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer11 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("TCL port:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer11->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlTclPort = new wxTextCtrl(this, ID_TEXTCTRLTCLPORT, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRLTCLPORT"));
	FlexGridSizer11->Add(TextCtrlTclPort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer11, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer3, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Hardware"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Interface:"), wxDefaultPosition, wxSize(60,13), 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ChoiceInterface = new wxChoice(this, ID_CHOICEDEBUGDEVICE, wxDefaultPosition, wxSize(139,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICEDEBUGDEVICE"));
	FlexGridSizer1->Add(ChoiceInterface, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer10 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Option:"), wxDefaultPosition, wxSize(60,13), 0, _T("ID_STATICTEXT8"));
	FlexGridSizer10->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ChoiceOption = new wxChoice(this, ID_CHOICEOPTION, wxDefaultPosition, wxSize(139,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICEOPTION"));
	FlexGridSizer10->Add(ChoiceOption, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer10, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Port:"), wxDefaultPosition, wxSize(60,13), 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ChoicePort = new wxChoice(this, ID_CHOICEPORT, wxDefaultPosition, wxSize(85,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICEPORT"));
	ChoicePort->SetSelection( ChoicePort->Append(_("LPT1")) );
	ChoicePort->Append(_("LPT2"));
	FlexGridSizer2->Add(ChoicePort, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Speed (kHz):"), wxDefaultPosition, wxSize(60,13), 0, _T("ID_STATICTEXT3"));
	FlexGridSizer3->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ChoiceSpeed = new wxChoice(this, ID_CHOICESPEED, wxDefaultPosition, wxSize(85,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICESPEED"));
	FlexGridSizer3->Add(ChoiceSpeed, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("Configuration"));
	FlexGridSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Configuration file:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer4->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlConfigFile = new wxTextCtrl(this, ID_TEXTCTRLCONFIGFILE, _("Text"), wxDefaultPosition, wxSize(203,21), 0, wxDefaultValidator, _T("ID_TEXTCTRLCONFIGFILE"));
	FlexGridSizer4->Add(TextCtrlConfigFile, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
	CheckBoxAuto = new wxCheckBox(this, ID_CHECKBOX1, _("Manage automatically"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBoxAuto->SetValue(false);
	FlexGridSizer5->Add(CheckBoxAuto, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer8->Add(StaticBoxSizer2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	GridSizer1->Add(FlexGridSizer8, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(GridSizer1);
	FileDialog = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE|wxFD_OPEN, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
	GridSizer1->SetSizeHints(this);
	
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenOCDConfig::OnButton2Click);
	Connect(ID_CHOICEDEBUGDEVICE,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&OpenOCDConfig::OnChoiceInterfaceSelect);
	//*)

    wxString str;

    // Polulate interface control
    for (unsigned n = 0; n < (sizeof g_OpenOCDDevs / sizeof g_OpenOCDDevs[0]); n++) {
        str = g_OpenOCDDevs[n].Name;
        ChoiceInterface->Append(str);
    }

    // Populate speed select
    ChoiceSpeed->Append(_T("10"));
    ChoiceSpeed->Append(_T("50"));
    ChoiceSpeed->Append(_T("100"));
    ChoiceSpeed->Append(_T("250"));
    ChoiceSpeed->Append(_T("500"));

	for (int n = 0; n < 10; n++) {
	    str = wxString::Format(_T("%d"), (n+1)*1000);
	    ChoiceSpeed->Append(str);
	}

    //LoadSettings();
    DoPorts();  // For wiggler parallel port selection
}

OpenOCDConfig::~OpenOCDConfig()
{
	//(*Destroy(OpenOCDConfig)
	//*)
}

void OpenOCDConfig::LoadSettings()
{
    wxString str;

    ChoiceInterface->SetStringSelection(m_Interface);
    ChoiceOption->SetStringSelection(m_Option);
    ChoiceSpeed->SetStringSelection(m_Speed);
    ChoicePort->SetSelection(m_DevicePort);

    TextCtrlConfigFile->SetValue(m_ConfigFile);
    CheckBoxAuto->SetValue(m_Auto);

    str = wxString::Format(_T("%d"), m_TelnetPort);
    TextCtrlTelnetPort->SetValue(str);

    str = wxString::Format(_T("%d"), m_TCLPort);
    TextCtrlTclPort->SetValue(str);

    TextCtrlProgramPath->SetValue(m_ProgramPath);

    str = wxString::Format(_T("%d"), m_GDBPort);
    TextCtrlGDBPort->SetValue(str);

    if (m_Interface == _T(""))
        ChoiceInterface->SetSelection(0);
    else
        ChoiceInterface->SetStringSelection(m_Interface);
    DoOptionSelect(ChoiceInterface->GetSelection());
    DoPorts();
}

void OpenOCDConfig::SaveSettings()
{
    wxString str;

    m_Interface = ChoiceInterface->GetStringSelection();
    m_Option = ChoiceOption->GetStringSelection();
    m_Speed = ChoiceSpeed->GetStringSelection();

    m_DevicePort = ChoicePort->GetSelection();

    m_ConfigFile = TextCtrlConfigFile->GetValue();
    m_Auto = CheckBoxAuto->GetValue();

    str = TextCtrlTelnetPort->GetValue();
    m_TelnetPort = atoi(str.mb_str());

    str = TextCtrlTclPort->GetValue();
    m_TCLPort = atoi(str.mb_str());

    m_ProgramPath = TextCtrlProgramPath->GetValue();

    str = TextCtrlGDBPort->GetValue();
    m_GDBPort = atoi(str.mb_str());
}

void OpenOCDConfig::DoPorts()
{
    wxString s = ChoiceInterface->GetStringSelection();

    if (s == _T("parport"))
        ChoicePort->Enable(true);
    else
        ChoicePort->Enable(false);
}

void OpenOCDConfig::OnButton2Click(wxCommandEvent& event)
{
    int nRet = FileDialog->ShowModal();
    if (nRet == wxID_OK) {
        TextCtrlProgramPath->SetValue(FileDialog->GetPath());
    }
}

void OpenOCDConfig::DoOptionSelect(int n)
{
    ChoiceOption->Clear();

    const wxChar **p = g_OpenOCDDevs[n].Options;
    if (!(p == NULL)) {

        int num = g_OpenOCDDevs[n].NumOpts;
        for (int i = 0; i < num; i++) {
            wxString str = p[i];
            ChoiceOption->Append(str);
        }

        ChoiceOption->Enable(true);
        if (m_Option == _T("")) {
            ChoiceOption->SetSelection(0);
        } else {
            ChoiceOption->SetStringSelection(m_Option);
        }
        DoPorts();
    } else {
        ChoiceOption->Enable(false);
    }
}

void OpenOCDConfig::OnChoiceInterfaceSelect(wxCommandEvent& event)
{
    int n = event.GetInt();
    DoOptionSelect(n);
}
