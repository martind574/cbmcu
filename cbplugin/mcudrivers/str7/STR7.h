#ifndef STR7_H
#define STR7_H

#include "mcuplugin.h"
#include "openocdplugin.h"
#include "configsettingspanel.h"

class STR7 : public mcuPlugin
{
    public:
        STR7();
        virtual ~STR7();
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

#endif // STM32_H
