#ifndef OPENOCDCONFIG_H
#define OPENOCDCONFIG_H

//(*Headers(OpenOCDConfig)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/filedlg.h>
#include <wx/choice.h>
#include <wx/button.h>
//*)

typedef struct OpenOCDDevs
{
    const wxChar *Name;
    const wxChar **Options;
    int NumOpts;   // Number of options for this device
} OpenOCDDevs;

class OpenOCDConfig: public wxPanel
{
	public:

		OpenOCDConfig(wxWindow* parent);
		virtual ~OpenOCDConfig();

		//(*Declarations(OpenOCDConfig)
		wxTextCtrl* TextCtrlGDBPort;
		wxStaticText* StaticText9;
		wxTextCtrl* TextCtrlConfigFile;
		wxChoice* ChoiceInterface;
		wxStaticText* StaticText2;
		wxStaticText* StaticText6;
		wxStaticText* StaticText8;
		wxChoice* ChoicePort;
		wxFileDialog* FileDialog;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxTextCtrl* TextCtrlTelnetPort;
		wxButton* Button2;
		wxStaticText* StaticText5;
		wxStaticText* StaticText7;
		wxChoice* ChoiceSpeed;
		wxChoice* ChoiceOption;
		wxTextCtrl* TextCtrlProgramPath;
		wxCheckBox* CheckBoxAuto;
		wxTextCtrl* TextCtrlTclPort;
		wxStaticText* StaticText4;
		//*)

        //int m_Device;
        wxString m_Interface;
        wxString m_Option;
        int m_DevicePort;
        wxString m_Speed;
        int m_GDBPort;
        wxString m_ConfigFile;
        int m_Auto;
        int m_TelnetPort;
        int m_TCLPort;
        wxString m_ProgramPath;

        void LoadSettings();
        void SaveSettings();
        void DoPorts();
        void DoOptionSelect(int n);

	protected:

		//(*Identifiers(OpenOCDConfig)
		static const long ID_STATICTEXT6;
		static const long ID_TEXTCTRLPROGRAMLOCATION;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT7;
		static const long ID_TEXTCTRLGDBPORT;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRLTELNETPORT;
		static const long ID_STATICTEXT9;
		static const long ID_TEXTCTRLTCLPORT;
		static const long ID_STATICTEXT1;
		static const long ID_CHOICEDEBUGDEVICE;
		static const long ID_STATICTEXT8;
		static const long ID_CHOICEOPTION;
		static const long ID_STATICTEXT2;
		static const long ID_CHOICEPORT;
		static const long ID_STATICTEXT3;
		static const long ID_CHOICESPEED;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRLCONFIGFILE;
		static const long ID_CHECKBOX1;
		//*)

	private:

		//(*Handlers(OpenOCDConfig)
		void OnButton2Click(wxCommandEvent& event);
		void OnChoiceInterfaceSelect(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
