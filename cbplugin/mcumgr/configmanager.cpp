#include "configmanager.h"

ConfigManager::ConfigManager()
{
    //ctor
}

ConfigManager::~ConfigManager()
{
    //dtor
}

bool ConfigManager::StartDFEnum(const wxString &path)
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

bool ConfigManager::GetNextDF(void)
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

bool ConfigManager::EndDFEnum(void)
{
    if (m_pDoc) {
        delete m_pDoc;
        m_pDoc = NULL;
        return true;
    }
    return false;
}
