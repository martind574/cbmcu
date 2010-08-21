//(*InternalHeaders(OpenOCDConfig)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "openocdconfig.h"
#include "openocdintdev.h"
//#include "openocddevftdi.h"
#include "openocddevs.h"

//(*IdInit(OpenOCDConfig)
const long OpenOCDConfig::ID_STATICTEXT1 = wxNewId();
const long OpenOCDConfig::ID_CHOICEDEBUGDEVICE = wxNewId();
const long OpenOCDConfig::ID_STATICTEXT8 = wxNewId();
const long OpenOCDConfig::ID_CHOICEOPTION = wxNewId();
const long OpenOCDConfig::ID_BUTTON_ADVANCED = wxNewId();
const long OpenOCDConfig::ID_STATICTEXT3 = wxNewId();
const long OpenOCDConfig::ID_CHOICESPEED = wxNewId();
const long OpenOCDConfig::ID_STATICTEXT4 = wxNewId();
const long OpenOCDConfig::ID_TEXTCTRLCONFIGFILE = wxNewId();
const long OpenOCDConfig::ID_CHECKBOX1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(OpenOCDConfig,wxPanel)
	//(*EventTable(OpenOCDConfig)
	//*)
END_EVENT_TABLE()

OpenOCDConfig::OpenOCDConfig(wxWindow* parent):
    //m_Device(0),
    m_Speed(_("0")),
    m_ConfigFile(_T("openocd.cfg")),
    m_Auto(true)
{
	//(*Initialize(OpenOCDConfig)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer4;
	wxFlexGridSizer* FlexGridSizer10;
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxGridSizer* GridSizer1;
	wxFlexGridSizer* FlexGridSizer8;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(340,315), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	GridSizer1 = new wxGridSizer(2, 1, 0, 0);
	FlexGridSizer8 = new wxFlexGridSizer(2, 1, 0, 0);
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
	ChoiceOption = new wxChoice(this, ID_CHOICEOPTION, wxDefaultPosition, wxSize(213,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICEOPTION"));
	FlexGridSizer10->Add(ChoiceOption, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(FlexGridSizer10, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	ButtonAdvanced = new wxButton(this, ID_BUTTON_ADVANCED, _("Advanced device settings..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_ADVANCED"));
	FlexGridSizer2->Add(ButtonAdvanced, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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
	GridSizer1->Add(FlexGridSizer8, 1, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	SetSizer(GridSizer1);
	GridSizer1->SetSizeHints(this);

	Connect(ID_CHOICEDEBUGDEVICE,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&OpenOCDConfig::OnChoiceInterfaceSelect);
	Connect(ID_BUTTON_ADVANCED,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenOCDConfig::OnButtonAdvancedClick);
	//*)

    wxString str;

    // Polulate interface control
    OpenOCDDevs devs;
    ChoiceInterface->Append(devs.GetInterfaceList());

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

    TextCtrlConfigFile->SetValue(m_ConfigFile);
    CheckBoxAuto->SetValue(m_Auto);

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

    m_ConfigFile = TextCtrlConfigFile->GetValue();
    m_Auto = CheckBoxAuto->GetValue();
}

void OpenOCDConfig::DoPorts()
{
    /*wxString s = ChoiceInterface->GetStringSelection();

    if (s == _T("parport"))
        ChoicePort->Enable(true);
    else
        ChoicePort->Enable(false);*/
}

void OpenOCDConfig::DoOptionSelect(int n)
{
    OpenOCDDevs IntDevs;
    OpenOCDIntDev *pDev;

    ChoiceOption->Clear();

    pDev = IntDevs.GetInterfaceDevice(n);

    if (pDev != NULL) {

        wxArrayString items = pDev->GetDeviceList();
        ChoiceOption->Append(items);

        ChoiceOption->Enable(true);
        int iopt = ChoiceOption->FindString(m_Option);

        if (iopt < 0) {
            ChoiceOption->SetSelection(0);
        } else {
            ChoiceOption->SetSelection(iopt);
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

void OpenOCDConfig::OnButtonAdvancedClick(wxCommandEvent& event)
{
    OpenOCDDevs Devs;
    OpenOCDIntDev *pIntDev;

    int nIndexInt = Devs.FindItem(ChoiceInterface->GetStringSelection());
    if (nIndexInt == -1)
        return;

    pIntDev = Devs.GetInterfaceDevice(nIndexInt);
    if (pIntDev == NULL)
        return;

    pIntDev->m_AdvOpts = m_AdvOpts;

    if (pIntDev->InvokeAdvancedOptions(this) >= 0) {
        // Save advanced options.
        m_AdvOpts = pIntDev->m_AdvOpts;
    }
}
