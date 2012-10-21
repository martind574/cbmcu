#include <sdk.h>

#include "remtargdrv.h"

//int idProcess = wxNewId(); // MD

GDBRemoteTargetDriver::GDBRemoteTargetDriver() :
    m_pProcess(0L)
{
}

GDBRemoteTargetDriver::~GDBRemoteTargetDriver()
{
}

int GDBRemoteTargetDriver::Start()
{
    return -1;
}

int GDBRemoteTargetDriver::Stop()
{
    return -1;
}

int GDBRemoteTargetDriver::Pause()
{
    return -1;
}

int GDBRemoteTargetDriver::Reset()
{
    return -1;
}

int GDBRemoteTargetDriver::Program()
{
    return -1;
}

void GDBRemoteTargetDriver::OnIdle(wxIdleEvent &event)
{
}

void GDBRemoteTargetDriver::OnProjectLoadingHook(cbProject* project, TiXmlElement* elem, bool loading)
{
}

void GDBRemoteTargetDriver::OnNewProject(cbProject *project)
{
}

void GDBRemoteTargetDriver::OnOpenProject(void)
{
}

bool GDBRemoteTargetDriver::OnConfigSettings(ConfigSettingsPanel *panel)
{
    return false;
}

bool GDBRemoteTargetDriver::OnConfigApply(void)
{
    return false;
}
