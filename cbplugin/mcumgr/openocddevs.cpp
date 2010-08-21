
#include "openocdintdev.h"
#include "openocddevftdi.h"
#include "openocddevparport.h"
#include "openocddevs.h"

static OpenOCDDevFTDI DevFTDI;
static OpenOCDDevParport DevParport;

OpenOCDDevEntry OpenOCDDevList[] = {
    {_T("dummy"), NULL},
    {_T("parport"), &DevParport},
    {_T("amt_jtagaccel"), NULL},
    {_T("ft2232"), &DevFTDI},
    {_T("ep93xx"), NULL},
    {_T("presto"), NULL},
    {_T("usbprog"), NULL},
    {_T("gw16012"), NULL},
    {_T("jlink"), NULL},
    {_T("rlink"), NULL},
    {_T("vsllink"), NULL},
    {_T("usb_blaster"), NULL}
};

OpenOCDDevs::OpenOCDDevs()
{
    //ctor
}

OpenOCDDevs::~OpenOCDDevs()
{
    //dtor
}

int OpenOCDDevs::GetInterfaceCount()
{
    return sizeof(OpenOCDDevList) / sizeof(OpenOCDDevList[0]);
}

wxArrayString OpenOCDDevs::GetInterfaceList()
{
    wxArrayString il;

    int num = GetInterfaceCount();
    for (int i = 0; i < num; i++)
        il.Add(OpenOCDDevList[i].Name);

    return il;
}

int OpenOCDDevs::FindItem(wxString item)
{
    int res = -1;
    int num = GetInterfaceCount();

    for (int i = 0; i < num; i++) {
        if (item == OpenOCDDevList[i].Name)
            res = i;
    }
    return res;
}

OpenOCDIntDev *OpenOCDDevs::GetInterfaceDevice(int item)
{
    if (item < GetInterfaceCount())
        return OpenOCDDevList[item].IntDev;
    return NULL;
}
