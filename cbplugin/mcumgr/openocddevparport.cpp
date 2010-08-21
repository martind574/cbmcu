#include <sdk.h>

#include "openocddevftdi.h"
#include "devparportadvopts.h"
#include "openocddevparport.h"

const wxChar *OpenOCD_parport[] = {
    _T("wiggler"),
    _T("wiggler2"),
    _T("wiggler_ntrst_inverted"),
    _T("old_amt_wiggler"),
    _T("chameleon"),
    _T("dlc5"),
    _T("triton"),
    _T("flashlink"),
    _T("arm-jtag"),
    _T("altium")
};

const int DevParport_LPTAddr[] = {0x378, 0x278, 0x3bc};

OpenOCDDevParport::OpenOCDDevParport()
{
    //ctor
}

OpenOCDDevParport::~OpenOCDDevParport()
{
    //dtor
}

int OpenOCDDevParport::GetDeviceCount()
{
    return sizeof(OpenOCD_parport) / sizeof(OpenOCD_parport[0]);
}

wxArrayString OpenOCDDevParport::GetDeviceList()
{
    wxArrayString list;

    int n = GetDeviceCount();

    for (int i = 0; i < n; i++)
        list.Add(OpenOCD_parport[i]);

    return list;
}

int OpenOCDDevParport::BuildDeviceString(int index, wxString &str)
{
    wxString ds;

    if (!(index < GetDeviceCount()))
        return -1;

    // Get port address from hash table.
    wxString strPort = AdvOptGet(_T("parport_addr"));
    int nPort;

    // Convert to raw hex.
    if (strPort == _T("LPT1"))
        nPort = 0x378;
    else if (strPort == _T("LPT2"))
        nPort = 0x278;
    else if (strPort == _T("LPT3"))
        nPort = 0x3BC;
    else nPort = 0x378;

    // Device description
    str.Printf(_T("\nparport port 0x%X"), nPort);
    str += _T("\nparport cable ");
    str += OpenOCD_parport[index];

    return 0;
}

int OpenOCDDevParport::FindItem(wxString item)
{
    int index = -1;
    int num = GetDeviceCount();

    for (int i = 0; i < num; i++) {
        if (item == OpenOCD_parport[i])
            index = i;
    }
    return index;
}

int OpenOCDDevParport::InvokeAdvancedOptions(wxWindow *parent)
{
    // Invoke port selection dialog.
    DevParportAdvOpts advOpts(parent);

    advOpts.m_Port = AdvOptGet(_T("parport_addr"));

    advOpts.InitDialog();

    if (advOpts.ShowModal() == wxID_OK) {

        // Write values to the hash map.
        AdvOptSet(_T("parport_addr"), advOpts.m_Port);

        return 1;
    }
    return 0;
}

