#ifndef REMOTETARGET_H_INCLUDED
#define REMOTETARGET_H_INCLUDED

#include <settings.h> // much of the SDK is here
#include <sdk_events.h>
#include <cbplugin.h>
#include "tinyxml/tinyxml.h"
//#include <simpletextlog.h>
#include <pipedprocess.h>
#include <wx/regex.h>
#include "configsettingspanel.h"

//class DebuggerGDB;

class GDBRemoteTargetDriver: public wxEvtHandler
{
public:
    GDBRemoteTargetDriver();
    virtual ~GDBRemoteTargetDriver();

    cbPlugin *m_pPlugin;         // Pointer to the plugin caller
    PipedProcess *m_pProcess;

//protected:
    virtual int Start(void);    // Start the remote driver
    virtual int Pause(void);    // Halt GDB
    virtual int Stop(void);     // Stop the remote driver
    virtual int Reset(void);    // Perform hardware reset
    virtual int Program(void);  // Program the target
    virtual void OnProjectLoadingHook(cbProject* project, TiXmlElement* elem, bool loading);
    virtual void OnOpenProject(void);
    virtual void OnIdle(wxIdleEvent &event);
    virtual bool OnConfigSettings(ConfigSettingsPanel *panel);
    virtual bool OnConfigApply(void);
};

#endif // REMOTETARGET_H_INCLUDED

