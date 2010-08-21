#ifndef OPENOCDCONFIG_H
#define OPENOCDCONFIG_H

//(*Headers(OpenOCDConfig)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/button.h>
//*)

#include "openocdintdev.h"
#include "openocddevs.h"

class OpenOCDConfig: public wxPanel
{
	public:

		OpenOCDConfig(wxWindow* parent);
		virtual ~OpenOCDConfig();

		//(*Declarations(OpenOCDConfig)
		wxTextCtrl* TextCtrlConfigFile;
		wxChoice* ChoiceInterface;
		wxStaticText* StaticText8;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxChoice* ChoiceSpeed;
		wxChoice* ChoiceOption;
		wxCheckBox* CheckBoxAuto;
		wxButton* ButtonAdvanced;
		wxStaticText* StaticText4;
		//*)

        //int m_Device;
        wxString m_Interface;
        wxString m_Option;
        int m_DevicePort;
        wxString m_Speed;
        wxString m_ConfigFile;
        int m_Auto;
        AdvOptsHash m_AdvOpts;

        void LoadSettings();
        void SaveSettings();
        void DoPorts();
        void DoOptionSelect(int n);

	protected:

		//(*Identifiers(OpenOCDConfig)
		static const long ID_STATICTEXT1;
		static const long ID_CHOICEDEBUGDEVICE;
		static const long ID_STATICTEXT8;
		static const long ID_CHOICEOPTION;
		static const long ID_BUTTON_ADVANCED;
		static const long ID_STATICTEXT3;
		static const long ID_CHOICESPEED;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRLCONFIGFILE;
		static const long ID_CHECKBOX1;
		//*)

	private:

		//(*Handlers(OpenOCDConfig)
		void OnChoiceInterfaceSelect(wxCommandEvent& event);
		void OnButtonAdvancedClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
