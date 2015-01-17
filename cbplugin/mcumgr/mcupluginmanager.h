#ifndef MCUPLUGINMANAGER_H
#define MCUPLUGINMANAGER_H

#include <wx/dir.h>
#include <wx/dynlib.h>
#include "tinyxml/tinyxml.h"

#include "configtargetdriver.h"
#include "mcuplugin.h"
#include "mcuconfigmanager.h"
#include "mcudebugdrivermanager.h"
#include "remtargdrv.h"

typedef mcuPlugin*(*mcuCreatePluginProc)();
typedef void(*mcuFreePluginProc)(mcuPlugin*);

class mcuPluginManager
{
    public:

        /* Return one and only instance of the MCU plugin manager. */
        static mcuPluginManager* GetInstance()
        {
            return &m_pm;
        }

        // Getters for various managers...
        mcuConfigManager *GetConfigManager();
        mcuDebugDriverManager *GetDebugDriverManager();

        //GDBRemoteTargetDriver *GetDebuggerDriver();
        wxString GetPluginPath();

        /* Interface to master plugin / entry points. The master
        plugin passes various events down to us. */
        void Attach();
        bool Close();
        void OnProjectLoadingHook(cbProject* project, TiXmlElement* elem, bool loading);
        void OnIdle(wxIdleEvent &event);

        // Set/Get the current micro and family
        bool SetMicro(const wxString &mcu, const wxString &family);
        bool GetMicro(wxString &mcu, wxString &family);

        // Remote debugger plugin handlers
        bool LoadPlugin(wxString name);
        bool UnloadPlugin(void);
        void RegisterPlugin(const wxString& name,
                            mcuCreatePluginProc createProc,
                            mcuFreePluginProc freeProc);
        bool IsPluginLoaded(void);

        bool InvokeConfigDialog(wxWindow *parent);
        bool ApplyConfigSettings(void);

        // MCU
        wxString m_mcuName;
        wxString m_family;

    protected:
    private:
        mcuPluginManager();
        virtual ~mcuPluginManager();
        static mcuPluginManager m_pm;   // The singleton
        wxDynamicLibrary *m_pMcuDrv;
        mcuPlugin *m_pPlugin;           // Current plugin object
        mcuCreatePluginProc m_pCreateProc;
        mcuFreePluginProc m_pFreeProc;
        wxDir m_dir;
        TiXmlDocument *m_pDoc;
        wxString m_dfPath;

        mcuConfigManager m_ConfigManager;           // Configuration manager
        mcuDebugDriverManager m_DebugDriverManager; // Debug driver manager
};

template<class T> class PluginRegistrantMCU
{
    public:
        /// @param name The plugin's name.
        PluginRegistrantMCU(const wxString& name)
        {
            mcuPluginManager::GetInstance()->RegisterPlugin(name, // plugin's name
                                                                &CreatePlugin, // creation
                                                                &FreePlugin); // destruction
        }

        static mcuPlugin* CreatePlugin()
        {
            return new T;
        }

        static void FreePlugin(mcuPlugin* plugin)
        {
            delete plugin;
        }

};

#endif // MCUPLUGINMANAGER_H
