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

/*
    \brief Called when mcumgr loads this plugin
*/
void STM32::OnAttach()
{
    // Register our driver object
    mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
    pDDM->RegisterDriver(&m_ocd);
}

void STM32::OnDetach()
{
    // We don't really have to do this..
    mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
    pDDM->RegisterDriver(NULL);
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
