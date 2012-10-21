#ifndef DEVPARPORTADVOPTS_H
#define DEVPARPORTADVOPTS_H

//(*Headers(DevParportAdvOpts)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class DevParportAdvOpts: public wxDialog
{
	public:

		DevParportAdvOpts(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~DevParportAdvOpts();

		//(*Declarations(DevParportAdvOpts)
		wxButton* ButtonOK;
		wxChoice* ChoicePort;
		wxStaticText* StaticText1;
		wxButton* ButtonCancel;
		//*)

        void InitDialog();

		wxString m_Port;

	protected:

		//(*Identifiers(DevParportAdvOpts)
		static const long ID_STATICTEXT1;
		static const long ID_CHOICE_PARPORT;
		//*)

        void EndModal(int retCode);

	private:

		//(*Handlers(DevParportAdvOpts)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
