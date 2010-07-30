#ifndef MAINPANEL_H
#define MAINPANEL_H

//(*Headers(mainpanel)
#include <wx/treectrl.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/button.h>
//*)

#include "configurationpanel.h"

class mainpanel: public cbConfigurationPanel
{
	public:

		mainpanel(wxWindow* parent);
		virtual ~mainpanel();

		//(*Declarations(mainpanel)
		wxTreeCtrl* TreeCtrlMicros;
		wxButton* ButtonSettings;
		wxStaticText* StaticText1;
		wxButton* ButtonSelect;
		wxStaticText* StaticDevice;
		//*)

        wxString GetTitle() const { return _("MCU settings"); }
        wxString GetBitmapBaseName() const { return _T("profiler"); }
        //void OnCancel(){}
        void OnInitDialog();
        void PopulateTree();    // Populate tree control with MCU selection
        virtual void OnApply();
        virtual void OnCancel();

        wxString m_mcuName;
        wxString m_family;


	protected:

		//(*Identifiers(mainpanel)
		//*)

	private:

		//(*Handlers(mainpanel)
		void OnButtonSettingsClick(wxCommandEvent& event);
		void OnButtonSelectClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
