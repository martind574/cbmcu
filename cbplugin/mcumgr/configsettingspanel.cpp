#include "configsettingspanel.h"

//(*InternalHeaders(ConfigSettingsPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(ConfigSettingsPanel)
const long ConfigSettingsPanel::ID_NOTEBOOKCONFIGPANELS = wxNewId();
//*)

BEGIN_EVENT_TABLE(ConfigSettingsPanel,wxPanel)
	//(*EventTable(ConfigSettingsPanel)
	//*)
END_EVENT_TABLE()

ConfigSettingsPanel::ConfigSettingsPanel(wxWindow* parent)
{
	//(*Initialize(ConfigSettingsPanel)
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(520,526), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetMaxSize(wxSize(-1,-1));
	NotebookConfigPanels = new wxNotebook(this, ID_NOTEBOOKCONFIGPANELS, wxDefaultPosition, wxSize(520,544), 0, _T("ID_NOTEBOOKCONFIGPANELS"));
	//*)
}

ConfigSettingsPanel::~ConfigSettingsPanel()
{
	//(*Destroy(ConfigSettingsPanel)
	//*)
}

bool ConfigSettingsPanel::AddPage(wxPanel *panel, wxString &text)
{
    return NotebookConfigPanels->AddPage(panel, text);
}
