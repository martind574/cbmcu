#include "openocddlg.h"

//(*InternalHeaders(openocddlg)
#include <wx/xrc/xmlres.h>
//*)

//(*IdInit(openocddlg)
//*)

BEGIN_EVENT_TABLE(openocddlg,wxDialog)
	//(*EventTable(openocddlg)
	//*)
END_EVENT_TABLE()

openocddlg::openocddlg(wxWindow* parent) :
    m_Device(0),
    m_Speed(0),
    m_Port(0),
    m_ConfigFile(_T("openocd.cfg")),
    m_Auto(true)
{
	//(*Initialize(openocddlg)
	wxXmlResource::Get()->LoadObject(this,parent,_T("openocddlg"),_T("wxDialog"));
	StaticText1 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT1"));
	ChoiceDebugDevice = (wxChoice*)FindWindow(XRCID("ID_CHOICEDEBUGDEVICE"));
	StaticText2 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT2"));
	ChoicePort = (wxChoice*)FindWindow(XRCID("ID_CHOICEPORT"));
	StaticText3 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT3"));
	ChoiceSpeed = (wxChoice*)FindWindow(XRCID("ID_CHOICESPEED"));
	StaticText4 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT4"));
	TextCtrlConfigFile = (wxTextCtrl*)FindWindow(XRCID("ID_TEXTCTRLCONFIGFILE"));
	Button2 = (wxButton*)FindWindow(XRCID("ID_BUTTON2"));
	CheckBoxAuto = (wxCheckBox*)FindWindow(XRCID("ID_CHECKBOX1"));
	Button1 = (wxButton*)FindWindow(XRCID("ID_BUTTON1"));
	OpenOCD = (wxPanel*)FindWindow(XRCID("ID_OPENOCDPANEL"));
	NotebookOpenOCD = (wxNotebook*)FindWindow(XRCID("ID_NOTEBOOK1"));
	ButtonOK = (wxButton*)FindWindow(XRCID("ID_BUTTONOK"));
	ButtonCancel = (wxButton*)FindWindow(XRCID("ID_BUTTONCANCEL"));

	Connect(XRCID("ID_CHOICEDEBUGDEVICE"),wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&openocddlg::OnChoiceDebugDeviceSelect);
	Connect(XRCID("ID_BUTTON2"),wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&openocddlg::OnButton2Click);
	Connect(XRCID("ID_NOTEBOOK1"),wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&openocddlg::OnNotebook1PageChanged);
	Connect(XRCID("ID_BUTTONOK"),wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&openocddlg::OnButtonApplyClick);
	Connect(XRCID("ID_BUTTONCANCEL"),wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&openocddlg::OnButtonCancelClick);
	//*)

	// Populate speed select
	for (int n = 1; n < 10; n++) {
	    wxString str = wxString::Format(_T("%d"), n);
	    ChoiceSpeed->Append(str);
	}

    //LoadSettings();
    //DoPorts();  // For wiggler parallel port selection
}

openocddlg::~openocddlg()
{
	//(*Destroy(openocddlg)
	//*)
}


void openocddlg::OnNotebook1PageChanged(wxNotebookEvent& event)
{
}

void openocddlg::LoadSettings()
{
    ChoiceDebugDevice->SetSelection(m_Device);
    ChoiceSpeed->SetSelection(m_Speed);
    ChoicePort->SetSelection(m_Port);
    //wxString str = wxString::Format(_T("%d"), m_gr->m_GDBPort);
    //TextCtrlGDBPort->SetValue(str);
    TextCtrlConfigFile->SetValue(m_ConfigFile);
    CheckBoxAuto->SetValue(m_Auto);

    DoPorts();
}

void openocddlg::SaveSettings()
{
    m_Device = ChoiceDebugDevice->GetSelection();
    m_Speed = ChoiceSpeed->GetSelection();
    m_Port = ChoicePort->GetSelection();
    //wxString str = TextCtrlGDBPort->GetValue();
    //const wxChar *p = str.c_str();
    //m_gr->m_GDBPort = atoi(cbU2C(p));
    m_ConfigFile = TextCtrlConfigFile->GetValue();
    m_Auto = CheckBoxAuto->GetValue();
}

void openocddlg::OnButton2Click(wxCommandEvent& event)
{
}

void openocddlg::OnButtonApplyClick(wxCommandEvent& event)
{
    SaveSettings();
    EndModal(1);
}

void openocddlg::OnButtonCancelClick(wxCommandEvent& event)
{
    EndModal(0);
}

/*
    \brief Enable / disable parallel port wiggler port selection
*/
void openocddlg::DoPorts()
{
    int n = ChoiceDebugDevice->GetCurrentSelection();
    wxString s = ChoiceDebugDevice->GetString(n);

    if (s == _T("Wiggler"))
        ChoicePort->Enable(true);
    else
        ChoicePort->Enable(false);
}

void openocddlg::OnChoiceDebugDeviceSelect(wxCommandEvent& event)
{
    DoPorts();
}
