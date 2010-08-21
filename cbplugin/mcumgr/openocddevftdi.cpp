#include <sdk.h>
#include "devparportadvopts.h"
#include "openocddevftdi.h"

const FTDI_Devs OpenOCD_ft2232[] = {
    {_T("olimex-jtag"), _T("Olimex OpenOCD JTAG"), 0x15BA, 0x0003},
    {_T("jtagkey"), _T("Amontec JTAGkey"), 0x0403, 0xcff8},
    {_T("jtagkey"), _T("Amontec JTAGkey-2"), 0x0403, 0xcff8},
    {_T("jtagkey"), _T("Amontec JTAGkey-2P"), 0x0403, 0xcff8},
    {_T("ktlink"), _T("KT-LINK"), 0x0403, 0xbbe2},
    {_T("olimex-jtag"), _T("Olimex OpenOCD JTAG"), 0x15ba, 0x0003},
    {_T("olimex-jtag"), _T("Olimex OpenOCD JTAG ARM-USB-OCD-H"), 0x15ba, 0x002b},
    {_T("olimex-jtag"), _T("Olimex OpenOCD JTAG ARM-USB-TINY-H"), 0x15ba, 0x002a},
    {_T("olimex-jtag"), _T("Olimex OpenOCD JTAG TINY"), 0x15ba, 0x0004},
    {_T("stm32stick"), _T("STM32-PerformanceStick"), 0x0640, 0x002d},
    {_T("USB-A9260"), _T("Symphony SoundBite"), 0x0403, 0x6010},
    {_T("cortino"), _T("Cortino"), 0x0640, 0x0032}
};

OpenOCDDevFTDI::OpenOCDDevFTDI()
{
}

OpenOCDDevFTDI::~OpenOCDDevFTDI()
{
    //dtor
}

int OpenOCDDevFTDI::GetDeviceCount()
{
    return sizeof(OpenOCD_ft2232) / sizeof(OpenOCD_ft2232[0]);
}

wxArrayString OpenOCDDevFTDI::GetDeviceList()
{
    wxArrayString list;

    int n = sizeof(OpenOCD_ft2232) / sizeof(OpenOCD_ft2232[0]);

    for (int i = 0; i < n; i++)
        list.Add(OpenOCD_ft2232[i].DeviceDesc);

    return list;
}

int OpenOCDDevFTDI::BuildDeviceString(int index, wxString &str)
{
    wxString ds;

    if (!(index < GetDeviceCount()))
        return -1;

    // Device description
    str = _T("\nft2232_device_desc ");
    str += _T("\"");
    str += OpenOCD_ft2232[index].DeviceDesc;
    str += _T("\"");

    // Layout
    str += _T("\nft2232_layout ");
    str += _T("\"");
    str += OpenOCD_ft2232[index].Layout;
    str += _T("\"");

    // Vid / Pid
    ds.Printf(_T("\nft2232_vid_pid 0x%04x 0x%04x"),
        OpenOCD_ft2232[index].Vid, OpenOCD_ft2232[index].Pid);

    str += ds;

    return 0;
}

int OpenOCDDevFTDI::FindItem(wxString item)
{
    int index = -1;
    int num = GetDeviceCount();

    for (int i = 0; i < num; i++) {
        if (item == OpenOCD_ft2232[i].DeviceDesc)
            index = i;
    }
    return index;
}

int OpenOCDDevFTDI::InvokeAdvancedOptions(wxWindow *parent)
{
    return -1;
}
