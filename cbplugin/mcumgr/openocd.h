/*! \class OpenOCDDriver
    \brief Class for handling launch, terminate, and command interface to OpenOCD.

    OpenOCDDriver inherits GDBRemoteTargetDriver, which is instantiated by a plugin by
    calling mcuPluginManager::GetInstance()->GetDebugDriverManager()->RegisterDriver().
    This way, each plugin can overide specific output related to the particular family.
*/


#ifndef OPENOCD_H_INCLUDED
#define OPENOCD_H_INCLUDED

#include <loggers.h>

#include "remtargdrv.h"
#include "telnetclient.h"
#include "configsettingspanel.h"
#include "openocdintdev.h"
#include "openocdconfig.h"
#include "openocdset.h"

typedef enum CRS
{
    Stopped,
    Stopping,
    Debugging,
    Programming
} CurrentRunState;

class OpenOCDDriver : public GDBRemoteTargetDriver
{
public:
    OpenOCDDriver();
    virtual ~OpenOCDDriver();

    virtual void OnNewProject(void);    // Called when new project created, to set project options etc
    virtual void OnOpenProject(void);   // Called when project opened, primarily to write config file
    virtual int Start(void);    // Start the remote driver
    virtual int Pause(void);    // Debug pause
    virtual int Stop(void);     // Stop the remote driver
    virtual int Reset(void);    // Perform hardware reset
    virtual int Program(void);  // Program the target

    int ProcessStop(void);
    virtual void ParseOutput(const wxString& output);           // Parse OpenOCD output
    bool IsStarted() {return (m_Pid == 0 ? false : true);}      // Return true if OpenOCD started

    void SetModified(void);     // Set settings modified flag
    bool IsModified(void);      // Query settings modified flag

protected:
    void OnProcOutput(wxCommandEvent& event);
    void OnProcError(wxCommandEvent& event);
    void OnProcTerminated(wxCommandEvent& event);
    virtual void OnIdle(wxIdleEvent& event);
    void OnTimer(wxTimerEvent& event);
    virtual int WriteConfigFile(void);
    virtual int OnWriteConfigFile(wxFile &file);
    virtual void OnProjectLoadingHook(cbProject* project, TiXmlElement* elem, bool loading);
    virtual bool OnConfigSettings(ConfigSettingsPanel *panel);
    virtual bool OnConfigApply(void);
    int Launch();        // Launch the program
    void Log(const wxString &msg);
    void ClearLog(void);
    int GetBaseAddress(int port);

    wxString m_Interface;       // Device interface
    wxString m_Option;          // Interface option
    //int m_DevicePort;
    wxString m_JTAGSpeed;       // JTAG speed
    int m_GDBPort;
    wxString m_ConfigFile;      // Config file
    bool m_Auto;                // Config file is auto generated
    int m_TelnetPort;           // Telnet port used to talk to OpenOCD
    int m_TCLPort;              // TCL control machine interface
    wxString m_ProgramPath;     // Actual location of OpenOCD binary
    AdvOptsHash m_AdvOpts;      // Advanced interface options

    OpenOCDConfig *m_Config;    // Mainly interface settings
    OpenOCDSet *m_Settings;     // Settings page

    //cbProject *m_pProject;
    bool m_bStarted;
    int m_HasDebugLog;
    int m_PageIndex;
    int m_Pid;
    TextCtrlLogger *m_pLog;
    wxTimer m_TimerPollDebugger;
    OpenOCDCmdInt *m_ocdint;
    bool m_FirstErr;
    CurrentRunState m_rs;       // Current run state
    bool m_Modified;            // Modified flag

    DECLARE_EVENT_TABLE()
};

#endif // OPENOCD_H_INCLUDED

