#include <sdk.h>
#include <configmanager.h>
#include <logmanager.h>
#include <projectmanager.h>
#include <pluginmanager.h>
#include <projectbuildtarget.h>
#include <cbproject.h>
#include <compilerfactory.h>

#include <wx/app.h>

#include "telnetclient.h"
#include "openocd.h"
#include "mcupluginmanager.h"
#include "openocdconfig.h"
#include "openocdset.h"
#include "openocddevs.h"

int idProcess = wxNewId();
int idTimer = wxNewId();

BEGIN_EVENT_TABLE(OpenOCDDriver, GDBRemoteTargetDriver)

    EVT_PIPEDPROCESS_STDOUT(idProcess, OpenOCDDriver::OnProcOutput)
    EVT_PIPEDPROCESS_STDERR(idProcess, OpenOCDDriver::OnProcError)
    EVT_PIPEDPROCESS_TERMINATED(idProcess, OpenOCDDriver::OnProcTerminated)
    EVT_TIMER(idTimer, OpenOCDDriver::OnTimer)

END_EVENT_TABLE()

/*!
    \brief Constructor. Initialise log window(s), timer and config manager.
*/
OpenOCDDriver::OpenOCDDriver() :
    GDBRemoteTargetDriver(),
    m_Interface(_T("parport")),
    m_Option(_T("wiggler")),
    m_JTAGSpeed(_("0")),
    m_GDBPort(2000),
    m_ConfigFile(_T("openocd.cfg")),
    m_Auto(true),
    m_TelnetPort(4444),
    m_TCLPort(6666),
    m_ProgramPath(_T("")),
    m_bStarted(false),
    m_Pid(0),
    m_pLog(NULL),
    m_ocdint(NULL),
    m_FirstErr(false),
    m_rs(Stopped),
    m_Modified(true)
{
    // Create log window
    wxBitmap *bmp;
    wxString prefix = ConfigManager::GetDataFolder() + _T("/images/");
    //m_HasDebugLog = Manager::Get()->GetConfigManager(_T("debugger"))->ReadBool(_T("debug_log"), false);
    //if (m_HasDebugLog)
    //{
        LogManager* msgMan = Manager::Get()->GetLogManager();

        m_pLog = new TextCtrlLogger(true);
        m_PageIndex = msgMan->SetLog(m_pLog);
        msgMan->Slot(m_PageIndex).title = _("OpenOCD");
        // set log image
        bmp = new wxBitmap(cbLoadBitmap(prefix + _T("contents_16x16.png"), wxBITMAP_TYPE_PNG));
        msgMan->Slot(m_PageIndex).icon = bmp;

		CodeBlocksLogEvent evtAdd(cbEVT_ADD_LOG_WINDOW, m_pLog, msgMan->Slot(m_PageIndex).title, msgMan->Slot(m_PageIndex).icon);
		Manager::Get()->ProcessEvent(evtAdd);
    //}
    m_TimerPollDebugger.SetOwner(this, idTimer);

    // Get program path from ConfigManager
    ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("mcumanager"));
    m_ProgramPath = cfg->Read(_T("/programpath"), _T(""));
}

/*!
    \brief Destructor. Stop process if already running, destroy log windows.
*/
OpenOCDDriver::~OpenOCDDriver()
{
    if (m_bStarted)
        Stop();
    if (!(m_pLog == NULL)) {
        LogManager* msgMan = Manager::Get()->GetLogManager();
        CodeBlocksLogEvent evtAdd(cbEVT_REMOVE_LOG_WINDOW, m_pLog, msgMan->Slot(m_PageIndex).title, msgMan->Slot(m_PageIndex).icon);
		Manager::Get()->ProcessEvent(evtAdd);
    }
}

/*!
    \brief Write message to log window.
    \param msg String containing message.
*/
void OpenOCDDriver::Log(const wxString &msg)
{
    Manager::Get()->GetLogManager()->Log(msg, m_PageIndex);
}

/*!
    \brief Clear the log window.
*/
void OpenOCDDriver::ClearLog(void)
{
    Manager::Get()->GetLogManager()->ClearLog(m_PageIndex);
}

/*!
    \brief Launch the OpenOCD program, and redirects standard output to the log window.
        Also starts the telnet / TCL command interface.
    \return 0 if success, -1 it stream output cannot be redirected. -2 if OpenOCD cannot be started.
        -3 if command interface cannot be started.
*/
int OpenOCDDriver::Launch(void)
{
    if (m_bStarted == true)
        return -2;  // Already running

    cbProject *project;

    project = Manager::Get()->GetProjectManager()->GetActiveProject();
    wxString tgt = project->GetActiveBuildTarget();
    ProjectBuildTarget *target = project->GetBuildTarget(tgt);
    Compiler *actualCompiler = CompilerFactory::GetCompiler(target ? target->GetCompilerID() : project->GetCompilerID());

    // Launch remote debug target (i.e OpenOCD)
    wxString masterPath = actualCompiler->GetMasterPath();
    while (masterPath.Last() == '\\' || masterPath.Last() == '/')
        masterPath.RemoveLast();

    wxString wdir;
    wxString cmdline;

    wdir = project ? project->GetBasePath() : _T(".");
    wxString args = wdir + m_ConfigFile; //_T("openocd.cfg");

    //cmdline = masterPath + wxFILE_SEP_PATH + _T("openocd") +
    //    wxFILE_SEP_PATH + _T("openocd.exe ") + args;
    cmdline = m_ProgramPath + _T(" -f ") + args;

    //TargetDebugLog(_T("Command-line: ") + cmdline);
    //TargetDebugLog(_T("Working dir : ") + wdir);

    m_pProcess = new PipedProcess((void**)&m_pProcess, this, idProcess, true, wdir);
    Log(_("Starting OpenOCD: "));

    m_Pid = wxExecute(cmdline, wxEXEC_ASYNC, m_pProcess);

    if (!m_Pid)
    {
        delete m_pProcess;
        m_pProcess = 0;
        Log(_("failed"));
        return -1;
    }
    else if (!m_pProcess->GetOutputStream())
    {
        delete m_pProcess;
        m_pProcess = 0;
        Log(_("failed (to get GDB remote's stdin)"));
        return -1;
    }
    else if (!m_pProcess->GetInputStream())
    {
        delete m_pProcess;
        m_pProcess = 0;
        Log(_("failed (to get GDB remote's stdout)"));
        return -1;
    }
    else if (!m_pProcess->GetErrorStream())
    {
        delete m_pProcess;
        m_pProcess = 0;
        Log(_("failed (to get GDB remote's stderr)"));
        return -1;
    }
    Log(_("done"));

    if (m_Pid == 0)
        return -1;  // Failed to run program

    m_bStarted = true;

    // although I don't really like these do-nothing loops, we must wait a small amount of time
    // for gdb to see if it really started: it may fail to load shared libs or whatever
    // the reason this is added is because I had a case where gdb would error and bail out
    // *while* the driver->Prepare() call was running below and hell broke loose...
    volatile int i = 50;
    while (i)
    {
		wxMilliSleep(1);
		Manager::Yield();
		--i;
    }

    if (m_bStarted == false)
        return -2;  // OpenOCD error

    // Start telnet/TCL command interface
    m_ocdint = new OpenOCDCmdInt();
    bool bRet = m_ocdint->OpenConn(_T("127.0.0.1"), m_TelnetPort);
    if (bRet == false)
        return -3;  // Could not start command interface

    m_TimerPollDebugger.Start(100);

    return 0;
}

/*!
    \brief Called when project is opened.

    We will just write the config file for now.
*/

void OpenOCDDriver::OnOpenProject(void)
{
    if (m_Auto == true) {

        Log(_T("Project opened, writing config file..."));

        // Write config file
        if (WriteConfigFile() < 0) {
            Log(_T("Writing config failed."));
        } else {
            Log(_T("Config file written."));
        }
    }
}

/*!
    \brief Start the debug process.

    The MCU plugin intercepts the cbEVT_DEBUGGER_STARTED message, which then calls
    mcuDebugDriverManager::Start(). If a valid GDBRemoteTargetDriver object exists, the
    GDBRemoteTargetDriver::Start() routine is called. As we have overided that function, our
    Start() is called here.
*/
int OpenOCDDriver::Start(void)
{
    int ret;

    ClearLog();
    Log(_T("Launching process..."));

    // Launch the process
    m_FirstErr = false;    // We want dialog box back
    ret = Launch();
    if (ret == 0) {
        m_rs = Debugging;
    }

    return ret;
}

/*!
    \brief Pause the debug process.

    This is done at the moment by executing the 'halt' to OpenOCD via the command interface.

    \return 0 on success, -1 on failure.
*/
int OpenOCDDriver::Pause(void)
{
    // Send halt to openOCD
    Log(_T("halt"));
    if (m_ocdint->Halt() == false)
        return -1;
    return 0;
}

/*!
    \brief Stop the debug process.

    Stop the command interface, terminate OpenOCD, stop the output polling timer.

    \return 0 on success, -1 on failure.
*/
int OpenOCDDriver::Stop(void)
{
    if (m_rs == Stopping) {
        Log(_T("Device is stopping..."));
        return -1;
    }

    if (m_rs == Stopped) {
        Log(_T("Device has already stopped."));
        return -1;
    }

    Log(_T("Stop"));
    if (!(m_Pid == 0)) {

        // Stop the command interface
        if (!(m_ocdint == NULL)) {
            m_ocdint->Destroy();      // Do not delete, destroy called automatically
            m_ocdint = NULL;
        }

        // Kill the process
        if (!(m_pProcess == NULL)) {

            m_pProcess->CloseOutput();
            m_pProcess->Kill(m_Pid, wxSIGKILL);

        }

        m_rs = Stopping;

        return 0;
    }
    return -1;
}

/*!
    \brief Execute a mcu reset.

    Reset the target. Experimental..
    \return 0 on success, -1 on failure.
*/
int OpenOCDDriver::Reset(void)
{
    // Send halt to openOCD
    Log(_T("reset"));
    if (m_ocdint->Reset() == false)
        return -1;
    return 0;
}

/*!
    \brief Program the microcontroller.

    This function is called outside of debug context. It launches OpenOCD for the sole
    purpose of programming the target. A TCL progflash() routine inside the OpenOCD config
    file must exist, and this routine is executed via the TCL/telnet interface.

    \return Return value from Launch()
*/
int OpenOCDDriver::Program(void)
{
    int ret;

    ClearLog();
    CodeBlocksLogEvent evtSwitch(cbEVT_SWITCH_TO_LOG_WINDOW, m_pLog);
    Manager::Get()->ProcessEvent(evtSwitch);

    Log(_T("Launching process..."));

    // Launch the process
    m_FirstErr = false;    // We want dialog box back
    ret = Launch();
    if (ret == 0) {

        // Let system know we are in programming state.
        m_rs = Programming;

        // Execute tcl script to program flash.
        Log(_T("Programming..."));
        m_ocdint->Program();

    }

    return ret;
}

/*!
    \brief Write OpenOCD config file.

    Writes common information to the config file, then calls OnWriteConfigFile so
    the plugins can write their information to the file.

    \return 0 on success, -1 on failure.
*/
int OpenOCDDriver::WriteConfigFile(void)
{
    char buf[256];

    // Write GDB target config file
    wxFile of;

    // Target file output dir
    ProjectManager* prjMan = Manager::Get()->GetProjectManager();
    cbProject* project = prjMan->GetActiveProject();

    wxString bt = project->GetBasePath();
    wxString cf = bt + m_ConfigFile;

    // Open target file
    bool ret = of.Open(cf, wxFile::write);
    if (ret == false)
        return -1;  // Cannot open file for writing

    // Write header
    of.Write(_T("# OpenOCD config file, auto generated by CodeBlocks"));

    // Write settings. Daemon config
    of.Write(_T("\n\n#daemon configuration\ntelnet_port "));
    sprintf(buf, "%d", m_TelnetPort);   // Get from config
    of.Write(buf, strlen(buf));

    // GDB port
    of.Write(_T("\ngdb_port "));
    sprintf(buf, "%d", m_GDBPort);
    of.Write(buf, strlen(buf));

    // TCL port
    of.Write(_T("\ntcl_port "));
    sprintf(buf, "%d", m_TCLPort);
    of.Write(buf, strlen(buf));

    //of.Write(_T("\ngdb_detach reset"));
    //of.Write(_T("gdb_memory_map enable\n"));
    //of.Write(_T("gdb_flash_program enable\n\n"));

    // Interface settings
    of.Write(_T("\n\n#interface\ninterface "));
    wxString str;

    // Write interface.
    of.Write(m_Interface);

    // Now find option index in array.
    int item;

    OpenOCDDevs devs;

    item = devs.FindItem(m_Interface);
    if (item == -1) {
        // The item was not found in the list.
        cbMessageBox(_T("The currently selected interface does not exist."), _("cbmcu plugin error"), wxICON_STOP);
        return -1;
    }

    OpenOCDIntDev *pDev = devs.GetInterfaceDevice(item);
    if (!(pDev == NULL)) {
        wxString str;

        item = pDev->FindItem(m_Option);
        if (item == -1) {
            cbMessageBox(_T("The currently selected device does not exist."), _("cbmcu plugin error"), wxICON_STOP);
        } else {
            pDev->BuildDeviceString(item, str);
            of.Write(str);
        }
    }

    of.Write(_T("\n\n"));

    // The plugin can write the rest
    int nRet = OnWriteConfigFile(of);
    if (nRet == 0) {
        // Plugin config failed.
        cbMessageBox(_T("Plugin has failed to write configuration"), _("cbmcu plugin error"), wxICON_STOP);
        nRet = -1;
    }
    of.Close();

    return nRet;
}

int OpenOCDDriver::OnWriteConfigFile(wxFile &file)
{
    return 1;
}

/*!
    \brief Console output (stdout).
    \param event wxCommandEvent containing output data.
*/
void OpenOCDDriver::OnProcOutput(wxCommandEvent &event)
{
    wxString msg = event.GetString();
    if (!msg.IsEmpty())
    {
        Log(event.GetString());
        ParseOutput(msg);
    }
}

/*!
    \brief Console output (stderr).
    \param event wxCommandEvent containing output data.
*/
void OpenOCDDriver::OnProcError(wxCommandEvent &event)
{
    wxString msg = event.GetString();
    if (!msg.IsEmpty())
    {
        Log(event.GetString());
        ParseOutput(msg);
    }
}

/*!
    \brief OpenOCD terminated.

    This function is called when OpenOCD exits or terminates.

    \param event wxCommandEvent containing output data.
*/
void OpenOCDDriver::OnProcTerminated(wxCommandEvent &event)
{
    wxString msg = event.GetString();
    if (!msg.IsEmpty())
    {
        ParseOutput(msg);
    }
    m_TimerPollDebugger.Stop();
    m_bStarted = false;
    m_rs = Stopped;
    m_Pid = 0;
    Log(_T("OpenOCD terminated"));
}

/*!
    \brief Process the output from OpenOCD.

    This is a virtual function and can be overidden by a plugin, so each
    plugin can have it's own output processing.

    \param output wxString containing output data from stdout and stderr streams.
*/
void OpenOCDDriver::ParseOutput(const wxString& output)
{
    // Display first dialog box error
    wxString trimLeft;
    trimLeft = output.Left(6);

    wxString err(_T("Error:"));

    if (trimLeft == err) {
        if (m_FirstErr == false) {
            // Only dialog box first error because they may be more than 1
            m_FirstErr = true;
            cbMessageBox(output, _("OpenOCD Error"), wxICON_STOP);
        }
    }

    if (m_rs == Programming) {
        trimLeft = output.Left(5);
        if (trimLeft == _T("wrote")) {
            Stop();
        }
    }
}

/*!
    \brief Idle time processing.

    OnIdle time here originates from the CodeBlocks message loop itself. The mcu plugin
    passes it to the mcu manager, which in turn passes it to us.

    \param event wxIdleEvent object.
*/
void OpenOCDDriver::OnIdle(wxIdleEvent& event)
{
    if (m_pProcess && ((PipedProcess*)m_pProcess)->HasInput())
        event.RequestMore();
    else
        event.Skip();
}

void OpenOCDDriver::OnTimer(wxTimerEvent& event)
{
    wxWakeUpIdle();
}

/*!
    \brief Get base address for the currently selected LPT port.
    \param port Port number to obtain base address for.
    \return Port address.
*/
int OpenOCDDriver::GetBaseAddress(int port)
{
    if (port == 0) return 0x378;
    if (port == 1) return 0x278;

    return 0;
}

/*!
    \brief Load / save project hook.

    When CodeBlocks loads and saves a file, we hook into the process here and load or save
    our parameters.

    \param project CodeBlocks project instance.
    \param elem XML element of root node.
    \param loading Flag set whether load / save, true = loading, false = saving.
*/
void OpenOCDDriver::OnProjectLoadingHook(cbProject* project, TiXmlElement* elem, bool loading)
{
    if (loading) {
        TiXmlElement* node = elem->FirstChildElement("gdbremote");
        if (node) {

            TiXmlElement *device = node->FirstChildElement("hardware");

            m_Interface = cbC2U(device->Attribute("interface"));
            m_Option = cbC2U(device->Attribute("option"));
            m_JTAGSpeed = cbC2U(device->Attribute("jtagspeed"));
            m_GDBPort = atoi(device->Attribute("gdbport"));
            m_ConfigFile = cbC2U(device->Attribute("configfile"));
            wxString strAuto = cbC2U(device->Attribute("auto"));
            m_TelnetPort = atoi(device->Attribute("telnetport"));
            m_TCLPort = atoi(device->Attribute("tclport"));
            if (strAuto == _T("true"))
                m_Auto = true;
            else
                m_Auto = false;

            // Now get advanced options.
            TiXmlElement *advopts = node->FirstChildElement("advintopts");
            if (advopts) {

                TiXmlAttribute *attr = advopts->FirstAttribute();
                while (attr) {

                    // Populate hash map with attributes.
                    wxString key = cbC2U(attr->Name());
                    wxString value = cbC2U(attr->Value());

                    m_AdvOpts[key] = value;

                    attr = attr->Next();
                }
            }

        } else {
            m_Interface = _T("parport");
            m_Option = _T("wiggler");
            m_JTAGSpeed = _T("0");
            m_ConfigFile = _T("openocd.cfg");
            m_Auto = true;
            m_TelnetPort = 4444;
            m_GDBPort = 2000;
            m_TCLPort = 6666;
            m_AdvOpts.clear();

        }
    } else {

        TiXmlElement* node = elem->FirstChildElement("gdbremote");
        if (!node)
            node = elem->InsertEndChild(TiXmlElement("gdbremote"))->ToElement();
        node->Clear();

        TiXmlElement *device = node->InsertEndChild(TiXmlElement("hardware"))->ToElement();

        device->SetAttribute("interface", cbU2C(m_Interface));
        device->SetAttribute("option", cbU2C(m_Option));
        device->SetAttribute("jtagspeed", cbU2C(m_JTAGSpeed));
        device->SetAttribute("gdbport", m_GDBPort);
        device->SetAttribute("configfile", cbU2C(m_ConfigFile));
        if (m_Auto == true)
            device->SetAttribute("auto", "true");
        else
            device->SetAttribute("auto", "false");
        device->SetAttribute("telnetport", m_TelnetPort);
        device->SetAttribute("tclport", m_TCLPort);

        // Write advanced options
        TiXmlElement *advopts = node->InsertEndChild(TiXmlElement("advintopts"))->ToElement();

        AdvOptsHash::iterator it;
        for( it = m_AdvOpts.begin(); it != m_AdvOpts.end(); ++it )
        {
            wxString key = it->first, value = it->second;
            // do something useful with key and value

            advopts->SetAttribute(cbU2C(key), cbU2C(value));
        }

    }
}

/*!
    \brief Invoke settings dialog.

    Called from the mcuManager's InvokeConfigDialog().

    \param panel Instance of ConfigSettingsPanel we can add to.
    \return Always true.
*/
bool OpenOCDDriver::OnConfigSettings(ConfigSettingsPanel *panel)
{
    m_Config = new OpenOCDConfig(panel->NotebookConfigPanels);
    m_Settings = new OpenOCDSet(panel->NotebookConfigPanels);

    m_Config->m_Interface = m_Interface;
    m_Config->m_Option = m_Option;
    m_Config->m_Speed = m_JTAGSpeed;
    m_Config->m_Auto = m_Auto;
    m_Config->m_ConfigFile = m_ConfigFile;
    m_Config->m_AdvOpts = m_AdvOpts;

    m_Settings->m_ProgramPath = m_ProgramPath;
    m_Settings->m_GDBPort = m_GDBPort;
    m_Settings->m_TelnetPort = m_TelnetPort;
    m_Settings->m_TCLPort = m_TCLPort;

    // Now load the dialogs settings
    m_Config->LoadSettings();
    m_Settings->LoadSettings();

    // Add our pages
    wxString name(_T("&Interface"));
    panel->AddPage((wxPanel*)m_Config, name);
    name = _T("&Settings");
    panel->AddPage((wxPanel*)m_Settings, name);

    return true;
}

/*!
    \brief Apply settings.

    Called when the 'apply' button is clicked from the ConfigSettings dialog.

    \return Always true.
*/
bool OpenOCDDriver::OnConfigApply(void)
{
    m_Config->SaveSettings();
    m_Settings->SaveSettings();

    // Get data from interface panel.
    m_Interface = m_Config->m_Interface;
    m_Option = m_Config->m_Option;
    m_JTAGSpeed = m_Config->m_Speed;
    m_Auto = m_Config->m_Auto;
    m_ConfigFile = m_Config->m_ConfigFile;
    m_AdvOpts = m_Config->m_AdvOpts;

    // Get data from settings panel.
    m_ProgramPath = m_Settings->m_ProgramPath;
    m_GDBPort = m_Settings->m_GDBPort;
    m_TelnetPort = m_Settings->m_TelnetPort;
    m_TCLPort = m_Settings->m_TCLPort;

    ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("mcumanager"));
    cfg->Write(_T("/programpath"), m_ProgramPath);

    // Re-write config file
    if (m_Auto == true) {

        Log(_T("Settings changed, writing config file..."));

        // Write config file
        if (WriteConfigFile() < 0) {
            Log(_T("Writing config failed."));
            return -1;
        } else {
            Log(_T("Config file written."));
        }
    }

    return true;
}

/*!
    \brief Set modified flag.

    Call this whenever changes occurr that require re-write of openocd.cfg
*/
void OpenOCDDriver::SetModified(void)
{
    m_Modified = true;
}

/*!
    \brief Get modified flag.

    Query modified flag.
*/
bool OpenOCDDriver::IsModified(void)
{
    return m_Modified;
}
