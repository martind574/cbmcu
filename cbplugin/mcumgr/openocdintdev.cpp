#include "openocdintdev.h"

OpenOCDIntDev::OpenOCDIntDev()
{
}

OpenOCDIntDev::~OpenOCDIntDev()
{
}

int OpenOCDIntDev::GetDeviceCount()
{
    return 0;
}

wxArrayString OpenOCDIntDev::GetDeviceList()
{
    wxArrayString list;
    return list;
}

int OpenOCDIntDev::BuildDeviceString(int index, wxString &str)
{
    str = _T("");
    return -1;
}

int OpenOCDIntDev::FindItem(wxString item)
{
    return -1;
}

int OpenOCDIntDev::InvokeAdvancedOptions(wxWindow *parent)
{
    return -1;
}

void OpenOCDIntDev::AdvOptSet(wxString key, wxString opt)
{
    m_AdvOpts[key] = opt;
}

wxString OpenOCDIntDev::AdvOptGet(wxString key)
{
    return m_AdvOpts[key];
}

void OpenOCDIntDev::AdvOptClear()
{
    m_AdvOpts.clear();
}

