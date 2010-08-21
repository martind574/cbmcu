#ifndef OPENOCDDEVFTDI_H
#define OPENOCDDEVFTDI_H

#include "openocdintdev.h"

typedef struct
{
    const wxChar *Layout;
    const wxChar *DeviceDesc;
    const int Vid;
    const int Pid;
} FTDI_Devs;

class OpenOCDDevFTDI : public OpenOCDIntDev
{
    public:
        OpenOCDDevFTDI();
        virtual ~OpenOCDDevFTDI();

        int GetDeviceCount();
        wxArrayString GetDeviceList();
        int BuildDeviceString(int index, wxString &str);
        int FindItem(wxString item);
        int InvokeAdvancedOptions(wxWindow *parent);
    protected:
    private:
};

#endif // OPENOCDDEVFTDI_H
