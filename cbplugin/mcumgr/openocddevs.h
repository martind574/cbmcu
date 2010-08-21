#ifndef OPENOCDDEVS_H
#define OPENOCDDEVS_H

//#include "openocddevs.h"
#include "openocdintdev.h"

typedef struct
{
    const wxChar *Name;
    OpenOCDIntDev *IntDev;
} OpenOCDDevEntry;

class OpenOCDDevs
{
    public:
        OpenOCDDevs();
        virtual ~OpenOCDDevs();

        wxArrayString GetInterfaceList();
        int GetInterfaceCount();
        int FindItem(wxString item);
        OpenOCDIntDev *GetInterfaceDevice(int item);

    protected:
    private:
};

#endif // OPENOCDDEVS_H
