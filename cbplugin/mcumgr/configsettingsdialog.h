#ifndef CONFIGSETTINGSDIALOG_H
#define CONFIGSETTINGSDIALOG_H

//(*Headers(ConfigSettingsDialog)
#include <wx/sizer.h>
#include <wx/button.h>
#include "configsettingspanel.h"
#include <wx/dialog.h>
//*)

class ConfigSettingsDialog: public wxDialog
{
	public:

		ConfigSettingsDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ConfigSettingsDialog();

		//(*Declarations(ConfigSettingsDialog)
		ConfigSettingsPanel* CustomConfigPanel;
		wxButton* ButtonCancel;
		wxButton* ButtonOk;
		//*)

	protected:

		//(*Identifiers(ConfigSettingsDialog)
		static const long ID_CUSTOMCONFIGPANEL;
		static const long ID_BUTTONOK;
		static const long ID_BUTTONCANCEL;
		//*)

	private:

		//(*Handlers(ConfigSettingsDialog)
		void OnCustomConfigPanelPaint(wxPaintEvent& event);
		void OnButtonOkClick(wxCommandEvent& event);
		void OnButtonCancelClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
