#ifndef OPENOCDINTDEV_H
#define OPENOCDINTDEV_H

#include <wx/window.h>
#include <wx/hashmap.h>

WX_DECLARE_STRING_HASH_MAP(wxString, AdvOptsHash);

class OpenOCDIntDev
{
    public:
        OpenOCDIntDev();
        virtual ~OpenOCDIntDev();

        virtual int GetDeviceCount(void);
        virtual wxArrayString GetDeviceList(void);
        virtual int BuildDeviceString(int index, wxString &str);
        virtual int FindItem(wxString item);
        virtual int InvokeAdvancedOptions(wxWindow *parent);

        AdvOptsHash m_AdvOpts;

    protected:
        void AdvOptSet(wxString key, wxString opt);
        wxString AdvOptGet(wxString key);
        void AdvOptClear();
    private:
};

#endif // OPENOCDINTDEV_H
