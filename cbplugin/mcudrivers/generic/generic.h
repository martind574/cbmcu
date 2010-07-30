#ifndef GENERIC_H
#define GENERIC_H

#include "mcuplugin.h"
#include "openocdplugin.h"
#include "configsettingspanel.h"

class generic : public mcuPlugin
{
    public:
        generic();
        virtual ~generic();
        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnSetDevice(const wxString &part);
        virtual void OnConfigSettings(ConfigSettingsPanel *panel);
        virtual bool OnConfigApply(void);

        // Static OpenOCD instance
        static OpenOCDPlugin m_ocd;   // The singleton
        static OpenOCDPlugin* getOpenOCD()
        {
            return &m_ocd;
        }

    protected:
    private:
};

#endif // GENERIC_H
