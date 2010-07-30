#ifndef STM32GENERALOPTIONS_H
#define STM32GENERALOPTIONS_H

//(*Headers(STM32GeneralOptions)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
//*)

class STM32GeneralOptions: public wxPanel
{
	public:

		STM32GeneralOptions(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~STM32GeneralOptions();

		//(*Declarations(STM32GeneralOptions)
		wxStaticText* StaticText1;
		//*)

	protected:

		//(*Identifiers(STM32GeneralOptions)
		static const long ID_STATICTEXT1;
		//*)

	private:

		//(*Handlers(STM32GeneralOptions)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
