#ifndef OPENOCD_H
#define OPENOCD_H

#include <wx/file.h>
#include "mcupluginmanager.h"
#include "openocd.h"


class OpenOCDPlugin : public OpenOCDDriver
{
    public:
        OpenOCDPlugin();
        virtual ~OpenOCDPlugin();
        int OnWriteConfigFile(wxFile &file);
        void OnNewProject(cbProject *project);
        bool ReadConfigData();

        wxString m_FlashSize;
        wxString m_RAMSize;

    protected:
    private:
};

#endif // OPENOCD_H
