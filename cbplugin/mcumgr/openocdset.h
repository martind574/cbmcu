#ifndef OPENOCDSET_H
#define OPENOCDSET_H

//(*Headers(OpenOCDSet)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/filedlg.h>
#include <wx/button.h>
//*)

class OpenOCDSet: public wxPanel
{
	public:

		OpenOCDSet(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~OpenOCDSet();

		//(*Declarations(OpenOCDSet)
		wxTextCtrl* TextCtrlGDBPort;
		wxTextCtrl* TextCtrlTCLPort;
		wxStaticText* StaticTextTCLPort;
		wxStaticText* StaticTextOpenOCD;
		wxFileDialog* FileDialogSelectLoc;
		wxTextCtrl* TextCtrlTelnetPort;
		wxStaticText* StaticTextGDBPort;
		wxTextCtrl* TextCtrlOpenOCDLoc;
		wxStaticText* StaticTextTelnetPort;
		wxButton* ButtonSelOpenOCD;
		//*)

        void LoadSettings(void);
        void SaveSettings(void);

		wxString m_ProgramPath;
		int m_GDBPort;
		int m_TelnetPort;
        int m_TCLPort;

	protected:

		//(*Identifiers(OpenOCDSet)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL_OPENOCDLOC;
		static const long ID_BUTTON_SELOPENOCD;
		static const long ID_STATICTEXT_TCLPORT;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT_TELNETPORT;
		static const long ID_TEXTCTRL_TELNETPORT;
		static const long ID_STATICTEXT_GDBPORT;
		static const long ID_TEXTCTRL_GDBPORT;
		//*)

	private:

		//(*Handlers(OpenOCDSet)
		void OnButtonSelOpenOCDClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
