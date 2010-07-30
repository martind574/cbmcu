#ifndef OPENODDLG_H
#define OPENODDLG_H

//(*Headers(openocddlg)
#include <wx/notebook.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class openocddlg: public wxDialog
{
	public:

		openocddlg(wxWindow* parent);
		virtual ~openocddlg();

		//(*Declarations(openocddlg)
		wxTextCtrl* TextCtrlConfigFile;
		wxStaticText* StaticText2;
		wxButton* Button1;
		wxButton* ButtonOK;
		wxChoice* ChoicePort;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxNotebook* NotebookOpenOCD;
		wxButton* Button2;
		wxButton* ButtonCancel;
		wxChoice* ChoiceSpeed;
		wxChoice* ChoiceDebugDevice;
		wxPanel* OpenOCD;
		wxCheckBox* CheckBoxAuto;
		wxStaticText* StaticText4;
		//*)

        void LoadSettings();

        int m_Device;
        int m_Speed;
        int m_Port;
        wxString m_ConfigFile;
        int m_Auto;

	protected:

		//(*Identifiers(openocddlg)
		//*)

        void SaveSettings();
        void DoPorts();

	private:

		//(*Handlers(openocddlg)
		void OnNotebook1PageChanged(wxNotebookEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnButtonApplyClick(wxCommandEvent& event);
		void OnButtonCancelClick(wxCommandEvent& event);
		void OnChoiceDebugDeviceSelect(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
