#ifndef CONFIGSETTINGSPANEL_H
#define CONFIGSETTINGSPANEL_H

//(*Headers(ConfigSettingsPanel)
#include <wx/notebook.h>
#include <wx/panel.h>
//*)

class ConfigSettingsPanel: public wxPanel
{
	public:

		ConfigSettingsPanel(wxWindow* parent);
		virtual ~ConfigSettingsPanel();

		//(*Declarations(ConfigSettingsPanel)
		wxNotebook* NotebookConfigPanels;
		//*)

        bool AddPage(wxPanel *panel, wxString &text);

	protected:

		//(*Identifiers(ConfigSettingsPanel)
		static const long ID_NOTEBOOKCONFIGPANELS;
		//*)

	private:

		//(*Handlers(ConfigSettingsPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
