/*
    Telnet client for communicating with OpenOCD
*/

#include <wx/socket.h>
#include "telnetclient.h"

TelnetClient::TelnetClient()
{
    m_open = false;
}

TelnetClient::~TelnetClient()
{
    if (m_open == true) {
        Destroy();
    }
}

bool TelnetClient::OpenConn(const wxString &host, unsigned short port)
{
    wxIPV4address addr;
    addr.Hostname(host);
    addr.Service(port);

    bool bSuccess = false;

    bool bRet = Connect(addr, false);
    bRet = WaitOnConnect(5, 0);
    if (bRet == true) {
        // Request completed, but was it accepted?
        bSuccess = IsConnected();
        if (bSuccess == true) {
            SetFlags(wxSOCKET_NOWAIT);
            m_open = true;
        }
    }
    return bSuccess;
}

void TelnetClient::Destroy(void)
{
    wxSocketBase::Destroy();
    m_open = false;
}


/* OpenOCD command interface */

OpenOCDCmdInt::OpenOCDCmdInt()
{
}

OpenOCDCmdInt::~OpenOCDCmdInt()
{
}

bool OpenOCDCmdInt::WriteCmd(const wxString &cmd)
{
    const wxChar *msg;

    //cmd += "\r";    // Slash R

    msg = cmd.c_str();
	wxUint32 len  = (wxStrlen(msg) + 1) * sizeof(wxChar);

    Write(msg, len);

    // Wait for response
    //wxChar *data = new wxChar[1024];
	//Read(data, 1024);
	//OutputDebugString(buffer);

	//delete[] data;

	return true;
}

bool OpenOCDCmdInt::WriteCmdResponse(const wxString &cmd)
{
    const wxChar *msg;

    //cmd += "\r";    // Slash R

    msg = cmd.c_str();
	wxUint32 len  = (wxStrlen(msg) + 1) * sizeof(wxChar);

    Write(msg, len);

    // Wait for response
    wxChar *data = new wxChar[1024];
	Read(data, 1024);
	//OutputDebugString(data);

	delete[] data;

	return true;
}

bool OpenOCDCmdInt::Halt(void)
{
    return WriteCmd(_T("halt\r"));
}

bool OpenOCDCmdInt::Reset(void)
{
    return WriteCmd(_T("reset\r"));
}

bool OpenOCDCmdInt::Program(void)
{
    return WriteCmdResponse(_T("progflash\r"));
}
