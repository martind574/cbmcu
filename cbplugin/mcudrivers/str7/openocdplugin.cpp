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
    wxString cfgFile;
    wxString familyCfg;
    unsigned long size;

    /* Read the openocd config file into a single wxString. */
    if (m_Part.Left(5) == _T("STR71")) {
        familyCfg = _T("str710.cfg");
    } else if (m_Part.Left(5) == _T("STR73")) {
        familyCfg = _T("str730.cfg");
    } else if (m_Part.Left(5) == _T("STR75")) {
        familyCfg = _T("str750.cfg");
    }

    wxString pluginDir = ConfigManager::GetFolder(sdPluginsGlobal);
    wxString mcuPluginDir = pluginDir + wxFILE_SEP_PATH + _T("mcudrv");

    wxFileInputStream cf(mcuPluginDir + wxFILE_SEP_PATH + familyCfg);
    if (cf.IsOk() == false)
        return 0;

    wxTextInputStream text(cf);
    while(cf.IsOk() && !cf.Eof() )
    {
        wxString line = text.ReadLine();
        cfgFile += line;
        cfgFile += '\n';
    }

    /* Now start placeholder replacement. First one speed. */
    cfgFile.Replace(_T("@@ADAPTER_KHZ@@"), m_JTAGSpeed);

    /* Set work area size. */
    m_RAMSize.ToULong(&size, 10);
    size *= 1024;
    s = wxString::Format(_T("%d"), size);

    cfgFile.Replace(_T("@@WORK_AREA_SIZE@@"), s);

     // Now we need to get target name from manager
    cbProject *project = Manager::Get()->GetProjectManager()->GetActiveProject();
    wxString strTarget = project->GetActiveBuildTarget();
    ProjectBuildTarget *target = project->GetBuildTarget(strTarget);
    wxString strOutFile = target->GetOutputFilename();
    while (strOutFile.Replace(_T("\\"), _T("/")));

    cfgFile.Replace(_T("@@OUTPUT_FILE@@"), strOutFile);

    /* Write the flash information. */
    size_t NumItems = m_FlashBlocks.GetCount();
    for (size_t n = 0; n < NumItems; n++) {

        FlashMem mem = m_FlashBlocks[n];

        wchar_t cbFlashBase[256];
        wchar_t cbFlashSize[256];

        /* Dynamically create placeholders. */
        wsprintf(cbFlashBase, _T("@@FLASH_BANK_BASE_%d@@"), n);
        wsprintf(cbFlashSize, _T("@@FLASH_BANK_SIZE_%d@@"), n);

        cfgFile.Replace(cbFlashBase, mem.m_Base);
        cfgFile.Replace(cbFlashSize, mem.m_Len);
    }

    file.Write(cfgFile);

    return 1;
}

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

        // Get RAM data
        TiXmlElement* ram = root->FirstChildElement("RAM");
        m_RAMSize = wxString::FromAscii(ram->Attribute("size"));
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
