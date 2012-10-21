#include <sdk.h> // Code::Blocks SDK
#include <sdk_events.h>
#include <configurationpanel.h>

#include "mcumain.h"
#include "mcupluginmanager.h"
#include "mainpanel.h"
#include "remtargdrv.h"
#include "openocd.h"

int idMenuSep = wxNewId();
int idMenuReset = wxNewId();
int idMenuProg = wxNewId();
int idMenuNew = wxNewId();
int idToolbarProg = XRCID("idProgram");

// events handling
BEGIN_EVENT_TABLE(mcu, cbPlugin)
    // add any events you want to handle here
    EVT_IDLE(mcu::OnIdle)
    EVT_MENU(idMenuReset, mcu::OnMenuReset)
    EVT_UPDATE_UI(idMenuReset, mcu::OnMenuResetUpdate)
    EVT_MENU(idMenuProg, mcu::OnMenuProgram)
    EVT_MENU(idToolbarProg, mcu::OnMenuProgram)
    //EVT_MENU(idMenuNew, mcu::OnMenuNew)
END_EVENT_TABLE()

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
    PluginRegistrant<mcu> reg(_T("mcu"));
}

// constructor
mcu::mcu()
{
    // Make sure our resources are available.
    // In the generated boilerplate code we have no resources but when
    // we add some, it will be nice that this code is in place already ;)
    if(!Manager::LoadResource(_T("mcu.zip")))
    {
        NotifyMissingFile(_T("mcu.zip"));
    }
    m_Open = false;
}

// destructor
mcu::~mcu()
{
    //delete m_pGDBDriver;
}

void mcu::OnAttach()
{
    // do whatever initialization you need for your plugin
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be TRUE...
    // You should check for it in other functions, because if it
    // is FALSE, it means that the application did *not* "load"
    // (see: does not need) this plugin...

    // Hook loading / saving procedure
    ProjectLoaderHooks::HookFunctorBase* myhook = new ProjectLoaderHooks::HookFunctor<mcu>(this, &mcu::OnProjectLoadingHook);
    m_HookId = ProjectLoaderHooks::RegisterHook(myhook);

    //Manager::Get()->RegisterEventSink(cbEVT_PROJECT_NEW, new cbEventFunctor<mcu, CodeBlocksEvent>(this, &mcu::OnProjectNew));
    Manager::Get()->RegisterEventSink(cbEVT_PROJECT_CLOSE, new cbEventFunctor<mcu, CodeBlocksEvent>(this, &mcu::OnProjectClose));
    Manager::Get()->RegisterEventSink(cbEVT_PROJECT_OPEN, new cbEventFunctor<mcu, CodeBlocksEvent>(this, &mcu::OnProjectOpen));
    Manager::Get()->RegisterEventSink(cbEVT_PROJECT_ACTIVATE, new cbEventFunctor<mcu, CodeBlocksEvent>(this, &mcu::OnProjectActivate));
    //Manager::Get()->RegisterEventSink(cbEVT_PROJECT_SAVE, new cbEventFunctor<mcu, CodeBlocksEvent>(this, &mcu::OnProjectSave));
    Manager::Get()->RegisterEventSink(cbEVT_DEBUGGER_STARTED, new cbEventFunctor<mcu, CodeBlocksEvent>(this, &mcu::OnStartDebug));
    //Manager::Get()->RegisterEventSink(cbEVT_DEBUGGER_PAUSED, new cbEventFunctor<mcu, CodeBlocksEvent>(this, &mcu::OnPauseDebug));
    Manager::Get()->RegisterEventSink(cbEVT_DEBUGGER_FINISHED, new cbEventFunctor<mcu, CodeBlocksEvent>(this, &mcu::OnStopDebug));

    mcuPluginManager::GetInstance()->Attach();
}

void mcu::OnRelease(bool appShutDown)
{
    // do de-initialization for your plugin
    // if appShutDown is true, the plugin is unloaded because Code::Blocks is being shut down,
    // which means you must not use any of the SDK Managers
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be FALSE...
}

int mcu::Configure()
{
    //create and display the configuration dialog for your plugin
    cbConfigurationDialog dlg(Manager::Get()->GetAppWindow(), wxID_ANY, _("cbmcu"));
    cbConfigurationPanel* panel = GetConfigurationPanel(&dlg);
    if (panel)
    {
        dlg.AttachConfigurationPanel(panel);
        PlaceWindow(&dlg);
        return dlg.ShowModal() == wxID_OK ? 0 : -1;
    }
    return -1;
}

void mcu::BuildMenu(wxMenuBar* menuBar)
{
    //The application is offering its menubar for your plugin,
    //to add any menu items you want...
    //Append any items you need in the menu...
    //NOTE: Be careful in here... The application's menubar is at your disposal.

    int pos = menuBar->FindMenu(_T("Debug"));
    wxMenu* ProjectMenu = menuBar->GetMenu(pos);
    ProjectMenu->AppendSeparator();     //(idMenuSep, _T(""), _T(""), wxITEM_SEPARATOR);
    //ProjectMenu->Append(idMenuReset, _T("Hardware reset"));
    ProjectMenu->Append(idMenuProg, _T("Program target"));

    //ProjectMenu->Append(idMenuOpenOCD, _T("OpenOCD settings..."));

    //NotImplemented(_T("mcu::BuildMenu()"));
}

void mcu::BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data)
{
    //Some library module is ready to display a pop-up menu.
    //Check the parameter \"type\" and see which module it is
    //and append any items you need in the menu...
    //TIP: for consistency, add a separator as the first item...
    NotImplemented(_T("mcu::BuildModuleMenu()"));
}

bool mcu::BuildToolBar(wxToolBar* toolBar)
{
    //The application is offering its toolbar for your plugin,
    //to add any toolbar items you want...
    //Append any items you need on the toolbar...
    //NotImplemented(_T("mcu::BuildToolBar()"));

    if (!IsAttached() || !toolBar)
        return false;
    //m_pTbar = toolBar;
    wxString my_16x16=Manager::isToolBar16x16(toolBar) ? _T("_16x16") : _T("");

    Manager::Get()->AddonToolBar(toolBar,_T("mcu_toolbar")+my_16x16);
    //m_ToolTarget = XRCCTRL(*toolBar, "idToolTarget", wxChoice);

    toolBar->Realize();
    toolBar->SetInitialSize();

    //DoRecreateTargetMenu(); // make sure the tool target combo is up-to-date

    // return true if you add toolbar items
    return true;
}

cbConfigurationPanel* mcu::GetProjectConfigurationPanel(wxWindow* parent, cbProject* project)
{
    if (!IsAttached())
        return 0;

    // Set defaults

    mcuPluginManager *plgMan = mcuPluginManager::GetInstance();

    mainpanel* dlg = new mainpanel(parent);
    dlg->m_mcuName = plgMan->m_mcuName;
    dlg->m_family = plgMan->m_family;
    dlg->OnInitDialog();

    return dlg;
}

void mcu::OnProjectLoadingHook(cbProject* project, TiXmlElement* elem, bool loading)
{
    mcuPluginManager *plgMan = mcuPluginManager::GetInstance();

    if (loading) {
        TiXmlElement* node = elem->FirstChildElement("mcu");
        if (node) {
            TiXmlElement *device = node->FirstChildElement("device");
            m_Family = cbC2U(device->Attribute("family"));
            m_Device = cbC2U(device->Attribute("device"));

            // We have to instantiate our plugin here, else the object
            // will not exist to load the plugin specific settings.
            mcuPluginManager *plgMan = mcuPluginManager::GetInstance();
            plgMan->SetMicro(m_Device, m_Family);

        } else {
            m_Family = _T("");
            m_Device = _T("");
        }
    } else {
        if (plgMan->GetMicro(m_Device, m_Family) == true) {

            TiXmlElement* node = elem->FirstChildElement("mcu");
            if (!node)
                node = elem->InsertEndChild(TiXmlElement("mcu"))->ToElement();
            node->Clear();
            TiXmlElement *device = node->InsertEndChild(TiXmlElement("device"))->ToElement();
            device->SetAttribute("family", cbU2C(m_Family));
            device->SetAttribute("device", cbU2C(m_Device));
        }
    }

    // Call GDB remote target driver hook
    plgMan->OnProjectLoadingHook(project, elem, loading);
}

void mcu::OnProjectNew(CodeBlocksEvent &event)
{
    cbConfigurationDialog dlg(Manager::Get()->GetAppWindow(), wxID_ANY, _("Settings"));
    cbConfigurationPanel* panel = GetProjectConfigurationPanel(&dlg, event.GetProject());
    if (panel)
    {
        dlg.AttachConfigurationPanel(panel);
        PlaceWindow(&dlg);
        if (dlg.ShowModal() == wxID_OK) {

            mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
            pDDM->OnNewProject(event.GetProject());
            event.SetInt(0);
        }
    }

    // Indicate failure.
    event.SetInt(-1);
}

void mcu::OnProjectOpen(CodeBlocksEvent &event)
{
    //if (m_Device == _T("")) {
        //cbMessageBox(_T("No MCU set, please select a device."), _T("Warning"));
        //return;     // No device is set
    //}
    /* OnProjectActivate will write config file. We won't call
    mcuPluginManager::GetInstance()->GetDebugDriverManager()->OnOpenProject() here as
    cbProject object not actually valid yet. */
    m_Open = true;
}

void mcu::OnProjectActivate(CodeBlocksEvent &event)
{
    if (m_Open == true) {
        // Tell debug driver manager that project is opened
        mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
        pDDM->OnOpenProject();
        m_Open = false;
    }
}

/*void mcu::OnProjectSave(CodeBlocksEvent &event)
{
    // Gets called after load/save hook
}*/

void mcu::OnProjectClose(CodeBlocksEvent &event)
{
    mcuPluginManager::GetInstance()->Close();
}

void mcu::OnIdle(wxIdleEvent &event)
{
    mcuPluginManager::GetInstance()->OnIdle(event);
}

void mcu::OnStartDebug(CodeBlocksEvent &event)
{
    mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
    int nRet = (int)pDDM->Start();
    event.SetInt(nRet);                   // Set return integer for GDB plugin
}

void mcu::OnPauseDebug(CodeBlocksEvent &event)
{
    mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
    int nRet = (int)pDDM->Pause();
    event.SetInt(nRet);                   // Set return integer for GDB plugin
}

void mcu::OnStopDebug(CodeBlocksEvent &event)
{
    mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
    int nRet = (int)pDDM->Stop();
    event.SetInt(nRet);                   // Set return integer for GDB plugin
}

/*! \brief Hardware reset
    Issue a hardware reset to the microcontroller
*/
void mcu::OnMenuReset(wxCommandEvent& event)
{
    mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
    int nRet = (int)pDDM->Reset();
    event.SetInt(nRet);
}

void mcu::OnMenuResetUpdate(wxUpdateUIEvent& event)
{
    mcuPluginManager *pMgr = mcuPluginManager::GetInstance();
    event.Enable(pMgr->IsPluginLoaded());
}

void mcu::OnMenuProgram(wxCommandEvent& event)
{
    mcuDebugDriverManager *pDDM = mcuPluginManager::GetInstance()->GetDebugDriverManager();
    int nRet = (int)pDDM->Program();
    event.SetInt(nRet);
}
