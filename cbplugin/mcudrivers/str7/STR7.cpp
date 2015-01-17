#include <sdk.h> // Code::Blocks SDK

#include "mcupluginmanager.h"
#include "mcudebugdrivermanager.h"
#include "STR7.h"
#include "STR7generaloptions.h"

OpenOCDPlugin STR7::m_ocd; // Create an OpenOCD instance

namespace
{
    PluginRegistrantMCU<STR7> reg(_T("STR7"));
}

STR7::STR7()
{
    //ctor
}

STR7::~STR7()
{
    //dtor
}

/*
    \brief Called when mcumgr loads this plugin
*/
void STR7::OnAttach()
{
    // Register our driver object
    mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
    pDDM->RegisterDebugDriver(&m_ocd);
}

void STR7::OnDetach()
{
    // We don't really have to do this..
    mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
    pDDM->RegisterDebugDriver(NULL);
}

void STR7::OnSetDevice(const wxString &part)
{
    // Get micro configuration options
    m_ocd.m_Part = part;
    m_ocd.ReadConfigData();
}

void STR7::OnConfigSettings(ConfigSettingsPanel *panel)
{
    /*m_Config = new STR7GeneralOptions(panel->NotebookConfigPanels);
    m_Config->m_UnprotectFlash = m_ocd.m_UnprotectFlash;
    m_Config->LoadSettings();

    wxString str = _T("STR7");
    panel->AddPage((wxPanel*)m_Config, str);*/
}

bool STR7::OnConfigApply(void)
{
    return true;
}
