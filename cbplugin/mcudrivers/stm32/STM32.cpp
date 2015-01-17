#include <sdk.h> // Code::Blocks SDK

#include "mcupluginmanager.h"
#include "STM32generaloptions.h"
#include "STM32.h"

OpenOCDPlugin STM32::m_ocd; // Create an OpenOCD instance

namespace
{
    PluginRegistrantMCU<STM32> reg(_T("STM32"));
}

STM32::STM32()
{
    //ctor
}

STM32::~STM32()
{
    //dtor
}

/** \brief This is called when the mcu manager loads this plugin
 *
 * From here we instantiate the one and only mcuDebugDriverManager object.
 */
void STM32::OnAttach()
{
    // Register our driver objects
    mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
    pDDM->RegisterDebugDriver(&m_ocd);

}

/** \brief This is called when the mcu manager unloads this plugin
 *
 * From here we instantiate the one and only mcuDebugDriverManager object.
 */
void STM32::OnDetach()
{
    // We don't really have to do this..
    mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
    pDDM->RegisterDebugDriver(NULL);
}

void STM32::OnSetDevice(const wxString &part)
{
    // Get micro configuration options
    m_ocd.ReadConfigData();
}

void STM32::OnConfigSettings(ConfigSettingsPanel *panel)
{
    STM32GeneralOptions *config = new STM32GeneralOptions(panel->NotebookConfigPanels);

    wxString str = _T("STM32");
    panel->AddPage((wxPanel*)config, str);
}

bool STM32::OnConfigApply(void)
{
    return false;
}

void STM32::OnProjectNew(cbProject *project)
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

