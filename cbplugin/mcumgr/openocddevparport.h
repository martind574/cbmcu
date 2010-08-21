#ifndef OPENOCDDEVPARPORT_H
#define OPENOCDDEVPARPORT_H

#include "openocddevftdi.h"

class OpenOCDDevParport : public OpenOCDIntDev
{
    public:
        OpenOCDDevParport();
        virtual ~OpenOCDDevParport();

        int GetDeviceCount();
        wxArrayString GetDeviceList();
        int BuildDeviceString(int index, wxString &str);
        int FindItem(wxString item);
        int InvokeAdvancedOptions(wxWindow *parent);

    protected:
    private:
        int m_ParportAddr;
};

#endif // OPENOCDDEVPARPORT_H
