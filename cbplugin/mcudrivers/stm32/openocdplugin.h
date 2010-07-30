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
        //unsigned Dispatch(unsigned code, void *din, void *dout);
        int OnWriteConfigFile(wxFile &file);
        //void DevSpecDlg();
        bool ReadConfigData();

        wxString m_FlashSize;
        wxString m_RAMSize;

    protected:
    private:
};

#endif // OPENOCD_H
