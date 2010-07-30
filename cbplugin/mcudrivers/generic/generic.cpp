#include <sdk.h> // Code::Blocks SDK

#include "mcupluginmanager.h"
#include "mcudebugdrivermanager.h"
#include "generic.h"

OpenOCDPlugin generic::m_ocd; // Create an OpenOCD instance

namespace
{
    PluginRegistrantMCU<generic> reg(_T("generic"));
}

generic::generic()
{
    //ctor
}

generic::~generic()
{
    //dtor
}

/*
    \brief Called when mcumgr loads this plugin
*/
void generic::OnAttach()
{
    // Register our driver object
    mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
    pDDM->RegisterDriver(&m_ocd);
}

void generic::OnDetach()
{
    // We don't really have to do this..
    mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
    pDDM->RegisterDriver(NULL);
}

void generic::OnSetDevice(const wxString &part)
{
    // Get micro configuration options
    //m_ocd.ReadConfigData();
}

void generic::OnConfigSettings(ConfigSettingsPanel *panel)
{
}

bool generic::OnConfigApply(void)
{
    return false;
}
