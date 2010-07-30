#include "mcupluginmanager.h"

static const wxString McuDescFileMask = _T("*.xml");

mcuConfigManager::mcuConfigManager()
{
    //ctor
}

mcuConfigManager::~mcuConfigManager()
{
    //dtor
}

bool mcuConfigManager::StartDFEnum(const wxString &path)
{
    wxString filename;

    // Start directory search
    if(!wxDirExists(path))
        return false;

    m_dfPath = path;
    m_dir.Open(m_dfPath);

    if (!m_dir.IsOpened())
        return false;

    bool ok = m_dir.GetFirst(&filename, McuDescFileMask, wxDIR_FILES);
    if (ok == true) {

        if (m_pDoc) {
            delete m_pDoc;  // Delete last
        }

        wxString fullPath;

        fullPath = path + wxFILE_SEP_PATH + filename;

        m_pDoc = new TiXmlDocument(fullPath.mb_str());
        //m_pDoc = new TiXmlDocument((const char*)"STM32.xml");

        if (!m_pDoc->LoadFile()) {
            delete m_pDoc;
            m_pDoc = NULL;
            return false;
        }

        // File ready for processing
        return true;
    }
    return false;
}

bool mcuConfigManager::GetNextDF(void)
{
    wxString filename;

    bool ok = m_dir.GetNext(&filename);
    if (ok == true) {

        if (m_pDoc) {
            delete m_pDoc;  // Delete last
        }

        wxString fullPath;

        fullPath = m_dfPath + wxFILE_SEP_PATH + filename;

        m_pDoc = new TiXmlDocument(fullPath.mb_str());
        //m_pDoc = new TiXmlDocument((const char*)"STM32.xml");

        if (!m_pDoc->LoadFile()) {
            delete m_pDoc;
            m_pDoc = NULL;
            return false;
        }

        // File ready for processing
        return true;
    }
    return false;
}

bool mcuConfigManager::EndDFEnum(void)
{
    if (m_pDoc) {
        delete m_pDoc;
        m_pDoc = NULL;
        return true;
    }
    return false;
}

TiXmlDocument *mcuConfigManager::OpenConfigFile()
{
    mcuPluginManager *mcuMgr = mcuPluginManager::GetInstance();
    wxString path = mcuMgr->GetPluginPath();

    /* We open the config file relevant to the family of the selected
    micro */
    wxString mcu, family;

    mcuMgr->GetMicro(mcu, family);
    path += wxFILE_SEP_PATH + family + _T(".xml");
    m_pDoc = new TiXmlDocument(path.mb_str());

    if (!m_pDoc->LoadFile()) {
        delete m_pDoc;
        m_pDoc = NULL;
        return NULL;
    }

    // File ready for processing
    return m_pDoc;
}

/*
    brief Position XML file at target micro
*/
TiXmlElement* mcuConfigManager::FindTarget()
{
    mcuPluginManager *mcuMgr = mcuPluginManager::GetInstance();

    wxString mcu, family, name;
    mcuMgr->GetMicro(mcu, family);

    TiXmlElement* root = m_pDoc->FirstChildElement("DeviceList");
    if ( root )
    {
        // Iterate through until mcu found

        TiXmlElement* device = root->FirstChildElement("Device");
        while (device) {

            name = wxString::FromAscii(device->Attribute("name"));
            if (name == mcu)
                return device;

            device = device->NextSiblingElement("Device");
        }
    }
    return NULL;
}

bool mcuConfigManager::CloseConfigFile()
{
    if (!(m_pDoc == NULL)) {
        delete m_pDoc;
        m_pDoc = NULL;
        return true;
    }
    return false;
}
