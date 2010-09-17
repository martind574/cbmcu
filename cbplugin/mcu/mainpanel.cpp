#include <sdk.h> // Code::Blocks SDK
#include <configmanager.h>

#include "mainpanel.h"
#include "mcupluginmanager.h"
#include "microtreeinfo.h"
#include "tinyxml/tinyxml.h"

//(*InternalHeaders(mainpanel)
#include <wx/xrc/xmlres.h>
//*)

//(*IdInit(mainpanel)
//*)

BEGIN_EVENT_TABLE(mainpanel,cbConfigurationPanel)
	//(*EventTable(mainpanel)
	//*)
END_EVENT_TABLE()

mainpanel::mainpanel(wxWindow* parent)
{
	//(*Initialize(mainpanel)
	wxXmlResource::Get()->LoadObject(this,parent,_T("mainpanel"),_T("wxPanel"));
	TreeCtrlMicros = (wxTreeCtrl*)FindWindow(XRCID("ID_TREECTRLMICROS"));
	ButtonSelect = (wxButton*)FindWindow(XRCID("ID_BUTTONSELECT"));
	StaticText1 = (wxStaticText*)FindWindow(XRCID("ID_STATICTEXT1"));
	StaticDevice = (wxStaticText*)FindWindow(XRCID("ID_STATICDEVICE"));
	ButtonSettings = (wxButton*)FindWindow(XRCID("ID_BUTTONSETTINGS"));

	Connect(XRCID("ID_BUTTONSELECT"),wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&mainpanel::OnButtonSelectClick);
	Connect(XRCID("ID_BUTTONSETTINGS"),wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&mainpanel::OnButtonSettingsClick);
	//*)
}

mainpanel::~mainpanel()
{
	//(*Destroy(mainpanel)
	//*)
}

void mainpanel::PopulateTree(void)
{
    wxString pluginDir = ConfigManager::GetFolder(sdPluginsGlobal);
    wxString mcuPluginDir = pluginDir + wxFILE_SEP_PATH + _T("mcudrv");

    mcuPluginManager *plgMan = mcuPluginManager::GetInstance();
    mcuConfigManager *cfgMan = plgMan->GetConfigManager();

    bool ret = cfgMan->StartDFEnum(mcuPluginDir);
    if (ret == false)
        return;

    wxTreeItemId treeRoot = TreeCtrlMicros->AddRoot(_T("Devices"));

    do {

        TiXmlDocument *doc = cfgMan->getXMLDoc();

        wxString name, family;
        wxTreeItemId parent;

        TiXmlElement* root = doc->FirstChildElement("DeviceList");
        if ( root )
        {
            family = wxString::FromAscii(root->Attribute("family"));
            parent = TreeCtrlMicros->AppendItem(treeRoot, family);   // Add family name as root node
            MicroTreeInfo *pInfo = new MicroTreeInfo;
            pInfo->m_mcuName = _T("");
            pInfo->m_family = _T("");
            pInfo->m_bRoot = true;
            TreeCtrlMicros->SetItemData(parent, pInfo);      // Mark as root node

            // Iterate through until

            TiXmlElement* device = root->FirstChildElement("Device");
            while (device) {

                name = wxString::FromAscii(device->Attribute("name"));
                wxTreeItemId child = TreeCtrlMicros->AppendItem(parent, name);

                MicroTreeInfo *pInfo = new MicroTreeInfo;
                pInfo->m_mcuName = name;
                pInfo->m_family = family;
                pInfo->m_bRoot = false;
                TreeCtrlMicros->SetItemData(child, pInfo);      // Mark as root node

                device = device->NextSiblingElement("Device");
            }
        }
    } while (cfgMan->GetNextDF());

    cfgMan->EndDFEnum();
}


void mainpanel::OnInitDialog()
{
    PopulateTree();

    // Set default MCU name and family
    if (m_mcuName == _T("")) {
        StaticDevice->SetLabel(_T("[None selected]"));
    } else {
        StaticDevice->SetLabel(m_mcuName);
        //wxTreeItemId id = TreeCtrl1->Find
    }
    // Call base ?
}

void mainpanel::OnButtonSettingsClick(wxCommandEvent& event)
{
    mcuPluginManager *pMgr = mcuPluginManager::GetInstance();
    int nRet = (int)pMgr->InvokeConfigDialog(this);
}

void mainpanel::OnButtonSelectClick(wxCommandEvent& event)
{
    // Get selected device
    wxTreeItemId id = TreeCtrlMicros->GetSelection();

    // Is there a valid item?
    MicroTreeInfo *pInfo = (MicroTreeInfo*)TreeCtrlMicros->GetItemData(id);
    if (pInfo == NULL)
        return;

    // Is it a leaf node?
    if (pInfo->m_bRoot == true)
        return;

    // Set names
    m_mcuName = pInfo->m_mcuName;
    m_family = pInfo->m_family;

    // Its a valid leaf node, set changes
    StaticDevice->SetLabel(pInfo->m_mcuName);

    // Set new micro
    mcuPluginManager *plgMan = mcuPluginManager::GetInstance();
    plgMan->SetMicro(m_mcuName, m_family);
}

void mainpanel::OnApply(void)
{}

void mainpanel::OnCancel(void)
{}
