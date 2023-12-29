#include "addproject.hpp"
#include "resource.h"
#include "projectrecord.hpp"
#include "zrestdb.hpp"
#include "db.hpp"
#include "log.hpp"
#include "languages.hpp"
#include <atlbase.h>
typedef std::basic_string <TCHAR> stringt;

BOOL CALLBACK AddProjectProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        SetFocus(GetDlgItem(hwnd, IDC_EDITNOM));
        SendMessage(GetDlgItem(hwnd, IDB_APOK), BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
        return FALSE;
    
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {

        case IDB_APCANCEL:
            EndDialog(hwnd, wParam);
            return TRUE;
        case IDB_APOK:
            auto fieldName = GetDlgItem(hwnd, IDC_EDITNOM);
            auto fieldDesc = GetDlgItem(hwnd, IDC_EDITDESC);
            TCHAR buffer[4096];
            GetWindowText(fieldName, buffer, sizeof(buffer));
            std::string name(buffer);
            memset(buffer, 0, sizeof(buffer));
            GetWindowText(fieldDesc, buffer, sizeof(buffer));
            std::string desc(buffer);
            if (name.find("|") != std::string::npos || desc.find("|") != std::string::npos)
            {
                auto log = zrestlog::Log::getInstance()->getLogger();
                log->error(_("The character '|' is forbiden in the name or the description"));
                USES_CONVERSION;
                MessageBoxA(NULL, _("The character '|' is forbiden in the name or the description"),_("Error"),
                      MB_ICONERROR | MB_OK);
                return TRUE;
            }
            if (name.empty() || desc.empty())
            {
                auto log = zrestlog::Log::getInstance()->getLogger();
                log->error(_("Both field must not be empty"));
                USES_CONVERSION;
                MessageBoxA(NULL, _("Both field must not be empty"), _("Error"),
                    MB_ICONERROR | MB_OK);
                return TRUE;
            }
            zrestmodel::ProjectRecord prj;
            prj.id = zrestdb::db::getInstance()->generateId();
            prj.name = name;
            prj.description = desc;
            prj.save();
            EndDialog(hwnd, wParam);
            return TRUE;

        }
    }
    return FALSE;
}