#ifndef TELNETCLIENT_H
#define TELNETCLIENT_H

#include <wx/socket.h>

class TelnetClient : public wxSocketClient
{
    public:
        TelnetClient();
        virtual ~TelnetClient();
        bool OpenConn(const wxString&, unsigned short port);
        void Destroy(void);

        wxSocketClient m_sock;
        bool m_open;

    protected:
    private:
};

/* !
    OpenOCD command interface
*/
class OpenOCDCmdInt : public TelnetClient
{
    public:
        OpenOCDCmdInt();
        ~OpenOCDCmdInt();

        bool Halt(void);    // Send the halt command
        bool Reset(void);   // Send the reset command
        bool Program(void); // Program target

    private:
        bool WriteCmd(const wxString &);    // Write open OCD command and wait for response
        bool WriteCmdResponse(const wxString &);

};

#endif // TELNETCLIENT_H
