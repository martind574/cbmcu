#ifndef STR7GENERALOPTIONS_H
#define STR7GENERALOPTIONS_H

//(*Headers(STR7GeneralOptions)
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
//*)

class STR7GeneralOptions: public wxPanel
{
	public:

		STR7GeneralOptions(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~STR7GeneralOptions();
		bool SaveSettings(void);
		void LoadSettings(void);

		//(*Declarations(STR7GeneralOptions)
		wxCheckBox* CheckBoxUnprotect;
		//*)

    bool m_UnprotectFlash;

	protected:

		//(*Identifiers(STR7GeneralOptions)
		static const long ID_CHECKBOXUNPROTECT;
		//*)

	private:

		//(*Handlers(STR7GeneralOptions)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
