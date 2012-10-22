
#include <sdk.h>
#include <configmanager.h>

#include "mcupluginmanager.h"
#include "mcuplugin.h"
#include "openocd.h"
#include "remtargdrv.h"
#include "configsettingsdialog.h"


mcuPluginManager mcuPluginManager::m_pm;
static const wxString PluginPath = _T("mcudrv");

mcuPluginManager::mcuPluginManager() :
    m_pMcuDrv(NULL),
    m_pPlugin(NULL),
    m_pDoc(NULL)
{
    //ctor
}

mcuPluginManager::~mcuPluginManager()
{
    //dtor
}

mcuConfigManager *mcuPluginManager::GetConfigManager()
{
    return &m_ConfigManager;
}

mcuDebugDriverManager *mcuPluginManager::GetDebugDriverManager()
{
    return &m_DebugDriverManager;
}

wxString mcuPluginManager::GetPluginPath()
{
    wxString pluginDir = ConfigManager::GetFolder(sdPluginsGlobal);
    wxString mcuPluginDir = pluginDir + wxFILE_SEP_PATH + PluginPath;

    return mcuPluginDir;
}

void mcuPluginManager::Attach()
{
}

bool mcuPluginManager::Close()
{
    if (m_pPlugin)
	{
        m_pPlugin->OnDetach();
        m_mcuName = _T("");
        m_family = _T("");
        m_DebugDriverManager.RegisterDriver(NULL);  // Just in case plugin didnt do it
        return UnloadPlugin();
    }
    return false;
}

bool mcuPluginManager::SetMicro(const wxString &mcu, const wxString &family)
{
    bool ret;

    ret = false;

    // Is family name different?
    if (m_family != family) {

        ret = LoadPlugin(family);
        if (ret == false) {
            return false;
        }
    }

    // Store names
    m_mcuName = mcu;
    m_family = family;

    // Now we can safely set the part
    m_pPlugin->OnSetDevice(m_mcuName);

    // Load the plugin based on the family name
    return ret;
}

bool mcuPluginManager::GetMicro(wxString &mcu, wxString &family)
{
    if (m_mcuName == _T(""))
        return false;

    mcu = m_mcuName;
    family = m_family;

    return true;
}

bool mcuPluginManager::LoadPlugin(wxString name)
{
    if (!(m_pPlugin == NULL)) {
        Close();
    }

    m_pMcuDrv = new wxDynamicLibrary;
    wxDir dir;

    wxString pluginDir = ConfigManager::GetFolder(sdPluginsGlobal);
    wxString mcuPluginDir = pluginDir + wxFILE_SEP_PATH + _T("mcudrv");

    wxString pluginName;
    pluginName = mcuPluginDir + wxFILE_SEP_PATH + name;

    if (m_pMcuDrv->Load(pluginName) == false) {
        delete m_pMcuDrv;
        m_pMcuDrv = NULL;
        return false;
    }

    // Plugin should have registered itself by now...
    m_pPlugin->OnAttach();

    return true;
}

bool mcuPluginManager::UnloadPlugin(void)
{
    // Unload plugin, destructors etc...
    if (m_pFreeProc && m_pPlugin) {
        m_pFreeProc(m_pPlugin);
        m_pPlugin = NULL;
    } else {
        return false;
    }

    // Delete wxDynamicLibrary object...
    if (m_pMcuDrv == NULL)
        return false;
    delete m_pMcuDrv;
    m_pMcuDrv = NULL;
    return true;
}

bool mcuPluginManager::IsPluginLoaded(void)
{
    if (m_pPlugin == NULL)
        return false;
    return true;
}

void mcuPluginManager::RegisterPlugin(const wxString &name,
                            mcuCreatePluginProc createProc,
                            mcuFreePluginProc freeProc)
{
    m_pCreateProc = createProc;
    m_pFreeProc = freeProc;
    m_pPlugin = m_pCreateProc();
}

void mcuPluginManager::OnIdle(wxIdleEvent &event)
{
    m_DebugDriverManager.OnIdle(event);
}

void mcuPluginManager::OnProjectLoadingHook(cbProject* project, TiXmlElement* elem, bool loading)
{
    m_DebugDriverManager.OnProjectLoadingHook(project, elem, loading);
}

bool mcuPluginManager::InvokeConfigDialog(wxWindow *parent)
{
    ConfigSettingsDialog dlg(parent);
    m_DebugDriverManager.OnConfigSettings(dlg.CustomConfigPanel); // Give to debug driver first
    if (m_pPlugin)
        m_pPlugin->OnConfigSettings(dlg.CustomConfigPanel);     // Then to plugin
    dlg.ShowModal();
    return true;
}

bool mcuPluginManager::ApplyConfigSettings(void)
{
    m_DebugDriverManager.OnConfigApply();
    if (m_pPlugin)
        m_pPlugin->OnConfigApply();     // Then to plugin
    return true;
}
