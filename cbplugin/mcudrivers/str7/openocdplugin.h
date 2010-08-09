#ifndef OPENOCD_H
#define OPENOCD_H

#include <wx/file.h>
#include <wx/dynarray.h>
#include "mcupluginmanager.h"
#include "openocd.h"
#include "STR7GeneralOptions.h"

class FlashMem;

WX_DECLARE_OBJARRAY(FlashMem, FlashBlockArray);

class FlashMem
{

public:

    wxString m_Size;
    wxString m_Block;
    wxString m_Base;
    wxString m_Len;
    wxString m_Variant;
};

class OpenOCDPlugin : public OpenOCDDriver
{
    public:
        OpenOCDPlugin();
        virtual ~OpenOCDPlugin();
        int OnWriteConfigFile(wxFile &file);
        bool ReadConfigData();
        void OnProjectLoadingHook(cbProject* project, TiXmlElement* elem, bool loading);
        bool OnConfigApply(void);
        bool OnConfigSettings(ConfigSettingsPanel *panel);

        void WriteConfigSTR71(wxFile &file);
        void WriteConfigSTR73(wxFile &file);
        void WriteConfigSTR75(wxFile &file);

        wxString m_Part;        // Part number of micro
        FlashBlockArray m_FlashBlocks;
        bool m_UnprotectFlash;
        wxString m_RAMSize;

        STR7GeneralOptions *m_Config;   // Config dialog extension

    protected:
    private:
};

#endif // OPENOCD_H
