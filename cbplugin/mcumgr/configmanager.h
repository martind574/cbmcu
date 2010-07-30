#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <wx/dir.h>
#include <wx/dynlib.h>
#include "tinyxml/tinyxml.h"

class mcuConfigManager
{
    public:
        mcuConfigManager();
        virtual ~mcuConfigManager();

        // For enumeration / searching of config XML files
        bool StartDFEnum(const wxString &path);
        bool EndDFEnum(void);
        bool GetNextDF(void);
        TiXmlDocument *getXMLDoc() { return m_pDoc; }

        // Open specific config file

    protected:
    private:
};

#endif // CONFIGMANAGER_H
