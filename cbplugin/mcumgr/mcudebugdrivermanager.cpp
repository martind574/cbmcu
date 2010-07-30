#include "mcudebugdrivermanager.h"

mcuDebugDriverManager::mcuDebugDriverManager()
{
    //ctor
}

mcuDebugDriverManager::~mcuDebugDriverManager()
{
    //dtor
}

GDBRemoteTargetDriver *mcuDebugDriverManager::GetDebuggerDriver()
{
    return m_pGDBTarg;
}

void mcuDebugDriverManager::OnIdle(wxIdleEvent &event)
{
    if (m_pGDBTarg) m_pGDBTarg->OnIdle(event);
}

void mcuDebugDriverManager::OnOpenProject(void)
{
    if (m_pGDBTarg)
        return m_pGDBTarg->OnOpenProject();
}

void mcuDebugDriverManager::OnProjectLoadingHook(cbProject* project, TiXmlElement* elem, bool loading)
{
    if (m_pGDBTarg) m_pGDBTarg->OnProjectLoadingHook(project, elem, loading);
}

int mcuDebugDriverManager::Start()
{
    if (m_pGDBTarg)
        return m_pGDBTarg->Start();
    return false;
}

int mcuDebugDriverManager::Pause()
{
    if (m_pGDBTarg)
        return m_pGDBTarg->Pause();
    return false;
}

int mcuDebugDriverManager::Stop()
{
    if (m_pGDBTarg)
        return m_pGDBTarg->Stop();
    return false;
}

int mcuDebugDriverManager::Reset()
{
    if (m_pGDBTarg)
        return m_pGDBTarg->Reset();
    return false;
}

int mcuDebugDriverManager::Program()
{
    if (m_pGDBTarg)
        return m_pGDBTarg->Program();
    return false;
}

void mcuDebugDriverManager::RegisterDriver(GDBRemoteTargetDriver *pDriver)
{
    m_pGDBTarg = pDriver;
}

bool mcuDebugDriverManager::OnConfigSettings(ConfigSettingsPanel *panel)
{
    if (m_pGDBTarg)
        return m_pGDBTarg->OnConfigSettings(panel);
    return false;
}

bool mcuDebugDriverManager::OnConfigApply(void)
{
    if (m_pGDBTarg)
        return m_pGDBTarg->OnConfigApply();
    return false;
}
