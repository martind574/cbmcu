#ifndef OPENOCDINTLOC_H
#define OPENOCDINTLOC_H

//(*Headers(openocdintloc)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statbox.h>
#include <wx/panel.h>
//*)

class openocdintloc: public wxPanel
{
	public:

		openocdintloc(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~openocdintloc();

		//(*Declarations(openocdintloc)
		wxStaticText* StaticText1;
		wxStaticBox* StaticBox1;
		//*)

	protected:

		//(*Identifiers(openocdintloc)
		static const long ID_STATICBOX1;
		static const long ID_STATICTEXT1;
		//*)

	private:

		//(*Handlers(openocdintloc)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
