#include <wx/file.h>
#include <wx/msgdlg.h>
#include <sdk.h>
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!

#include "openocdplugin.h"
#include "mcupluginmanager.h"
#include "mcuconfigmanager.h"

WX_DEFINE_OBJARRAY(FlashBlockArray);

OpenOCDPlugin::OpenOCDPlugin()
{
    m_UnprotectFlash = false;
}

OpenOCDPlugin::~OpenOCDPlugin()
{
    //dtor
}

int OpenOCDPlugin::OnWriteConfigFile(wxFile &file)
{
    wxString s, basePart;

    file.Write(_T("\n"));

    if (m_Part.Left(5) == _T("STR71")) {
        WriteConfigSTR71(file);
    } else if (m_Part.Left(5) == _T("STR73")) {
        WriteConfigSTR73(file);
    } else if (m_Part.Left(5) == _T("STR75")) {
        WriteConfigSTR75(file);
    }

    // JTAG speed and halt target
    file.Write(_T("\n\n# Init"));
    file.Write(_T("\njtag_khz 10"));
    file.Write(_T("\ninit"));
    file.Write(_T("\nsoft_reset_halt"));     // Always halt target

    return 1;
}

void OpenOCDPlugin::WriteConfigSTR71(wxFile &file)
{
    wxString s;

    file.Write(_T("\n\n# Use combined on interfaces or targets that can't set TRST/SRST separately"));
    file.Write(_T("\nreset_config trst_and_srst srst_pulls_trst"));

    file.Write(_T("\n\n# JTAG scan chain"));
    file.Write(_T("\njtag newtap str710 cpu -irlen 4 -ircapture 0x1 -irmask 0x0f -expected-id 0x3f0f0f0f"));
    file.Write(_T("\ntarget create str710.cpu arm7tdmi -endian little -chain-position str710.cpu -variant arm7tdmi"));

    // Write speed after reset issued
    //wxString s;
    //file.Write(_T("\nstr710.cpu configure -event reset-init { jtag_khz "));
    //file.Write(m_JTAGSpeed);
    //file.Write(_T("}"));

    if (m_UnprotectFlash == true) {
        file.Write(_T("\nstr710.cpu configure -event gdb-flash-erase-start { \
            \n\tflash protect 0 0 7 off \
            \n\tflash protect 1 0 1 off \
            \n}"));
    }

    file.Write(_T("\nstr710.cpu configure -work-area-virt 0 -work-area-phys 0x2000C000 -work-area-size 0x4000 -work-area-backup 0"));

    // Flash banks
    file.Write(_T("\n\n#flash bank str7x <base> <size> 0 0 <target#> <variant>"));
    size_t NumItems = m_FlashBlocks.GetCount();
    for (size_t n = 0; n < NumItems; n++) {

        FlashMem mem = m_FlashBlocks[n];

        s = wxString::Format(wxT("\nflash bank str7x %s %s 0 0 0 %s"),
            mem.m_Base.wx_str(), mem.m_Len.wx_str(), mem.m_Variant.wx_str());
        file.Write(s);
    }
}

void OpenOCDPlugin::WriteConfigSTR73(wxFile &file)
{
    // JTAG
    /*file.Write(_T("\ntarget create str710.cpu arm7tdmi -endian little -chain-position str710.cpu -variant arm7tdmi"));
    file.Write(_T("\nstr710.cpu configure -event reset-start { jtag_khz 10 }"));
    file.Write(_T("\nstr710.cpu configure -event reset-init { jtag_khz 6000 }"));
    file.Write(_T("\nstr710.cpu configure -event gdb-flash-erase-start { \
        \nflash protect 0 0 7 off \
        \nflash protect 1 0 1 off \
        \n}"));

    file.Write(_T("\nstr710.cpu configure -work-area-virt 0 -work-area-phys 0x2000C000 -work-area-size 0x4000 -work-area-backup 0"));

    //#flash bank str7x <base> <size> 0 0 <target#> <variant>
    //flash bank str7x 0x40000000 0x00040000 0 0 0 STR71x
    //flash bank str7x 0x400C0000 0x00004000 0 0 0 STR71x
    wxString s;
    s = wxString::Format(wxT("\nflash bank str7x %s %s 0 0 0 %s"),
        m_FlashBase.wx_str(), m_FlashLen.wx_str(), m_FlashVariant.wx_str());
    file.Write(s);*/

}

void OpenOCDPlugin::WriteConfigSTR75(wxFile &file)
{
    // JTAG
    /*file.Write(_T("\ntarget create str710.cpu arm7tdmi -endian little -chain-position str710.cpu -variant arm7tdmi"));
    file.Write(_T("\nstr710.cpu configure -event reset-start { jtag_khz 10 }"));
    file.Write(_T("\nstr710.cpu configure -event reset-init { jtag_khz 6000 }"));
    file.Write(_T("\nstr710.cpu configure -event gdb-flash-erase-start { \
        \nflash protect 0 0 7 off \
        \nflash protect 1 0 1 off \
        \n}"));

    file.Write(_T("\nstr710.cpu configure -work-area-virt 0 -work-area-phys 0x2000C000 -work-area-size 0x4000 -work-area-backup 0"));

    //#flash bank str7x <base> <size> 0 0 <target#> <variant>
    //flash bank str7x 0x40000000 0x00040000 0 0 0 STR71x
    //flash bank str7x 0x400C0000 0x00004000 0 0 0 STR71x
    wxString s;
    s = wxString::Format(wxT("\nflash bank str7x %s %s 0 0 0 %s"),
        m_FlashBase.wx_str(), m_FlashLen.wx_str(), m_FlashVariant.wx_str());
    file.Write(s); */
}

/*void OpenOCD::DevSpecDlg()
{
    STR7Opts od(Manager::Get()->GetAppWindow());
    od.ShowModal();
}*/

bool OpenOCDPlugin::ReadConfigData()
{
    FlashMem fm;

    // Read the configuration data
    mcuPluginManager *plgMan = mcuPluginManager::GetInstance();
    mcuConfigManager *cfgMgr = plgMan->GetConfigManager();
    TiXmlDocument* doc = cfgMgr->OpenConfigFile();
    if (doc == NULL)
        return false;

    // We have successfully opened the config file, now find out element
    TiXmlElement *root = cfgMgr->FindTarget();

    if (!(root == NULL)) {

        m_FlashBlocks.Empty();

        // Get flash data
        TiXmlElement* flash = root->FirstChildElement("Flash");

        while (flash) {

            // Get flash items from XML config file
            fm.m_Size = wxString::FromAscii(flash->Attribute("size"));
            fm.m_Block = wxString::FromAscii(flash->Attribute("block"));
            fm.m_Base = wxString::FromAscii(flash->Attribute("base"));
            fm.m_Len = wxString::FromAscii(flash->Attribute("len"));
            fm.m_Variant = wxString::FromAscii(flash->Attribute("variant"));

            m_FlashBlocks.Add(fm);

            flash = flash->NextSiblingElement("Flash");
        }
    }

    return true;
}

void OpenOCDPlugin::OnProjectLoadingHook(cbProject* project, TiXmlElement* elem, bool loading)
{
    OpenOCDDriver::OnProjectLoadingHook(project, elem, loading);    // Do this first as it looks clearer in file

    if (loading) {
        TiXmlElement* node = elem->FirstChildElement("gdbremote-STR7specific");
        if (node) {

            m_UnprotectFlash = (cbC2U(node->Attribute("unprotect_flash")) == _T("true")) ? true : false;

        } else {

            m_UnprotectFlash = false;

        }
    } else {
        TiXmlElement* node = elem->FirstChildElement("gdbremote-STR7specific");
        if (!node)
            node = elem->InsertEndChild(TiXmlElement("gdbremote-STR7specific"))->ToElement();
        node->Clear();

        if (m_UnprotectFlash == true)
            node->SetAttribute("unprotect_flash", "true");
        else
            node->SetAttribute("unprotect_flash", "false");
    }

}

bool OpenOCDPlugin::OnConfigSettings(ConfigSettingsPanel *panel)
{
    OpenOCDDriver::OnConfigSettings(panel);

    m_Config = new STR7GeneralOptions(panel->NotebookConfigPanels);
    m_Config->m_UnprotectFlash = m_UnprotectFlash;
    m_Config->LoadSettings();

    wxString str = _T("STR7");
    panel->AddPage((wxPanel*)m_Config, str);

    return true;
}

bool OpenOCDPlugin::OnConfigApply(void)
{
    OpenOCDDriver::OnConfigApply();
    m_UnprotectFlash = m_Config->m_UnprotectFlash;

    return true;
}
