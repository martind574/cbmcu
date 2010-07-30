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

    //file.Write(_T("\n\n#use combined on interfaces or targets that can't set TRST/SRST separately"));
    //file.Write(_T("\nreset_config trst_and_srst"));

    // Write scan chains
    file.Write(_T("\n\n#jtag scan chain: CPU"));
    file.Write(_T("\njtag newtap stm32 cpu -irlen 4 -ircapture 0x1 -irmask 0x0f -expected-id 0x3ba00477"));

    file.Write(_T("\n\n#jtag scan chain: BS"));
    file.Write(_T("\njtag newtap stm32 bs -irlen 5 -expected-id 0x06412041 -expected-id 0x06410041 -expected-id 0x16410041 -expected-id 0x06414041 -expected-id 0x06418041"));
    //file.Write(m_TapBS);

    // Create target
    file.Write(_T("\n\ntarget create stm32.cpu cortex_m3 -endian little -chain-position stm32.cpu"));

    m_RAMSize.ToULong(&size, 10);
    size *= 1024;
    s = wxString::Format(_T("%d"), size);

    file.Write(_T("\nstm32.cpu configure -work-area-phys 0x20000000 -work-area-size "));
    file.Write(s);
    file.Write(_T(" -work-area-backup 0"));

    file.Write(_T("\n\n#flash is probed"));
    file.Write(_T("\nflash bank stm32x 0 0 0 0 stm32.cpu"));

    //file.Write(_T("\n\n#GDB flash programming"));
    //file.Write(_T("\ngdb_memory_map enable"));
    //file.Write(_T("\ngdb_flash_program enable"));

    // Write flash programming routine called progflash. MCU plugin will call this routine
    // when programming button is pressed.
    file.Write(_T("\n\n#flash programming routine"));
    file.Write(_T("\nproc progflash {} {\n\tflash write_image erase "));

    // Now we need to get target name from manager
    cbProject *project = Manager::Get()->GetProjectManager()->GetActiveProject();
    wxString strTarget = project->GetActiveBuildTarget();
    ProjectBuildTarget *target = project->GetBuildTarget(strTarget);
    wxString strOutFile = target->GetOutputFilename();
    while (strOutFile.Replace(_T("\\"), _T("/")));

    file.Write(strOutFile);
    file.Write(_T("\n}"));

    file.Write(_T("\n\ninit\nreset halt\n"));

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
        TiXmlElement* flash = root->FirstChildElement("RAM");
        m_RAMSize = wxString::FromAscii(flash->Attribute("size"));
    }

    return true;
}
