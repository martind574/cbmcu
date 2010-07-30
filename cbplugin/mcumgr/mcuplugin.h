#ifndef MCUPLUGIN_H
#define MCUPLUGIN_H

#include "configsettingspanel.h"

class mcuPlugin
{
    public:
        mcuPlugin();
        virtual ~mcuPlugin();

        virtual void OnAttach(void) = 0;
        virtual void OnDetach(void) = 0;
        virtual void OnSetDevice(const wxString &part);
        virtual void OnConfigSettings(ConfigSettingsPanel *panel);
        virtual bool OnConfigApply(void);

    protected:
    private:
};

#endif // GRPLUGIN_H
