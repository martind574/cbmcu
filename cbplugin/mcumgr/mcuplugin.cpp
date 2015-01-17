#include <sdk.h> // Code::Blocks SDK

#include "configtargetdriver.h"
#include "mcupluginmanager.h"
#include "mcuplugin.h"

mcuPlugin::mcuPlugin()
{
    //ctor
}

mcuPlugin::~mcuPlugin()
{
    //dtor
}

void mcuPlugin::OnSetDevice(const wxString &part)
{
}

void mcuPlugin::OnConfigSettings(ConfigSettingsPanel *panel)
{
}

bool mcuPlugin::OnConfigApply(void)
{
    return true;
}

void mcuPlugin::OnProjectNew(cbProject *project)
{
}

