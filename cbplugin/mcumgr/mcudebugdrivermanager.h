#ifndef MCUDEBUGDRIVERMANAGER_H
#define MCUDEBUGDRIVERMANAGER_H

#include "remtargdrv.h"
#include "configsettingspanel.h"

class mcuDebugDriverManager
{
    friend class mcuPluginManager;

    public:
        mcuDebugDriverManager();
        virtual ~mcuDebugDriverManager();

        GDBRemoteTargetDriver *GetDebuggerDriver();     // Return pointer to dynamic debug driver object
        void RegisterDebugDriver(GDBRemoteTargetDriver *pDriver);

        void OnNewProject(cbProject *project);    // New project created
        void OnOpenProject(void);   // Called when project opened
        int Start(void);        // Launch currently created object
        int Pause(void);        // Pause / halt target
        int Stop(void);         // Stop a target
        int Reset(void);        // Hardware reset a target
        int Program(void);      // Program a target
        bool OnConfigSettings(ConfigSettingsPanel *panel);          // Invoke dialog box
        bool OnConfigApply(void);       // Apply settings

    protected:

        void OnProjectLoadingHook(cbProject* project, TiXmlElement* elem, bool loading);
        void OnIdle(wxIdleEvent &event);
        GDBRemoteTargetDriver *m_pGDBTarg;      // GDB remote driver (currently unique)

    private:
};

#endif // MCUDEBUGDRIVERMANAGER_H
