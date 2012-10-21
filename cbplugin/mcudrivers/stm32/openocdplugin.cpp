#include <wx/file.h>
#include <wx/msgdlg.h>
#include <sdk.h>

//#include "STM32Opts.h"
#include "openocdplugin.h"
#include "mcupluginmanager.h"
#include "mcuconfigmanager.h"

OpenOCDPlugin::OpenOCDPlugin()
{
    //ctor
}

OpenOCDPlugin::~OpenOCDPlugin()
{
    //dtor
}

int OpenOCDPlugin::OnWriteConfigFile(wxFile &file)
{
    wxString s;
    unsigned long size;
    wxString cfgFile;

    //wxString mcuPath = ConfigManager::GetFolder(sdDataGlobal) + _T("/mcudrv");
    wxString pluginDir = ConfigManager::GetFolder(sdPluginsGlobal);
    wxString mcuPluginDir = pluginDir + wxFILE_SEP_PATH + _T("mcudrv");

    wxFileInputStream cf(mcuPluginDir + wxFILE_SEP_PATH + _T("stm32.cfg"));
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

    /* Work area size. */
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

    file.Write(cfgFile);

    return 1;
}

bool OpenOCDPlugin::ReadConfigData()
{
    // Read the configuration data
    mcuPluginManager *plgMan = mcuPluginManager::GetInstance();
    mcuConfigManager *cfgMgr = plgMan->GetConfigManager();
    TiXmlDocument* doc = cfgMgr->OpenConfigFile();
    if (doc == NULL)
        return false;

    // We have successfully opened the config file, now find out element
    TiXmlElement *root = cfgMgr->FindTarget();

    if (!(root == NULL)) {
        // Get flash size
        TiXmlElement* ram = root->FirstChildElement("RAM");
        m_RAMSize = wxString::FromAscii(ram->Attribute("size"));
    }

    return true;
}

void OpenOCDPlugin::OnNewProject(cbProject *project)
{
    project->AddCompilerOption(_T("-mcpu=cortex-m3"));
    project->AddCompilerOption(_T("-mthumb"));
    project->AddCompilerOption(_T("-g"));
    project->AddCompilerOption(_T("-Wall"));
    project->AddCompilerOption(_T("-ffunction-sections"));
    project->AddCompilerOption(_T("-fdata-sections"));

    project->AddLinkerOption(_T("-Wl,--gc-sections"));
    project->AddLinkerOption(_T("-nostartfiles"));

    // Get output directory. */

    // Library config.
    project->AddCompilerOption(_T("-DUSE_STDPERIPH_DRIVER"));

    // Add target for flash memory.
    project->AddBuildTarget(_T("Flash"));
}
