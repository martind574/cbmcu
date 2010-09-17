#ifndef MICROTREEINFO_H
#define MICROTREEINFO_H

#include <wx/treectrl.h>

class MicroTreeInfo : public wxTreeItemData
{
    public:
        MicroTreeInfo();
        virtual ~MicroTreeInfo();

        wxString m_mcuName;
        wxString m_family;
        bool m_bRoot;

    protected:
    private:
};

#endif // MICROTREEINFO_H
