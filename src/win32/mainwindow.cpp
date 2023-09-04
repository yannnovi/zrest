#ifndef UNICODE
#define UNICODE
#endif 
#include "mainwindow.hpp"
#include "resource.h"
#include "log.hpp"
#include "db.hpp"
#include "projectrecord.hpp"
#include "requestmanager.hpp"
#include "instancewnd.hpp"
#include "addproject.hpp"
#include "languages.hpp"
#include <windows.h>
#include <atlbase.h>
#include <sstream>
#include <iostream>

#define IDB_QUIT 2001
#define IDB_NEW  2002
#define IDLB_MAINLISTBOX 2003
#define IDB_DEL 2004
zrestgui::MainWindow::MainWindow(HINSTANCE hInstance, HWND parent, int nCmdShow)
{
    auto log = zrestlog::Log::getInstance()->getLogger();
    log->error("saucisse");
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"ZRest";

    WNDCLASS wc = { };

    wc.lpfnWndProc = requestProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"ZRest",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        LoadMenuW(hInstance, L"MAINWMENU"),       // Menu
        hInstance,  // Instance handle
        this        // Additional application data
    );

    if (hwnd == NULL)
    {
        log->error(_("CreateWindowsEX error: {}."), GetLastError());
    }
    USES_CONVERSION;
    HWND hwndButtonQuit = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        A2T(_("Quit")),      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles 
        1260,         // x position 
        670,         // y position 
        100,        // Button width
        30,        // Button height
        hwnd,     // Parent window
        (HMENU)IDB_QUIT,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    if (hwndButtonQuit == NULL)
    {
        log->error(_("CreateWindows error: {}."), GetLastError());
    }

    HWND hwndButtonDelete = CreateWindowW(
        L"BUTTON",  // Predefined class; Unicode assumed 
        A2T(_("DeleteProject")),      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles 
        1260,         // x position 
        630,         // y position 
        100,        // Button width
        30,        // Button height
        hwnd,     // Parent window
        (HMENU)IDB_DEL,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    if (hwndButtonDelete == NULL)
    {
        log->error(_("CreateWindows error: {}."), GetLastError());
    }

    HWND hwndButtonNew = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        A2T(_("AddProjectButton")),      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        1260,         // x position 
        590,         // y position 
        100,        // Button width
        30,        // Button height
        hwnd,     // Parent window
        (HMENU)IDB_NEW,
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.
    if (hwndButtonNew == NULL)
    {
        log->error(_("CreateWindows error: {}."), GetLastError());
    }

    SetFocus(hwndButtonNew);
    // Adding a ListBox.
    HWND hListBox = CreateWindowEx(WS_EX_CLIENTEDGE
        , L"LISTBOX", NULL
        , WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | LBS_NOTIFY
        , 5, 5, 1220, 700
        , hwnd, (HMENU)IDLB_MAINLISTBOX, hInstance, NULL);
    if (hListBox == NULL)
    {
        log->error(_("CreateWindows error: {}."), GetLastError());
    }

    ShowWindow(hwnd, nCmdShow);
}

void zrestgui::MainWindow::afficheListe(HWND hwnd, HWND parent) {
    SendMessage(hwnd, LB_RESETCONTENT, 0, 0);

    auto  liste_projets = zrestdb::db::getInstance()->findAllProject();
    //MainCollectionsList
    for (auto& project : liste_projets)
    {
        std::string name = project.name;
        std::string desc = project.description;
        std::string ligne(name + "||" + desc);
        USES_CONVERSION;
        SendMessage(hwnd, LB_ADDSTRING, 0, (LPARAM)A2T(ligne.c_str()));
    }
    SetFocus(GetDlgItem(parent, IDB_NEW));
}

void zrestgui::MainWindow::effaceSelection(HWND hwnd) {
    auto log = zrestlog::Log::getInstance()->getLogger();
    DWORD dwSel = SendMessage(hwnd, LB_GETCURSEL, 0, 0);
    if (dwSel >= 0) {
        int size = SendMessage(hwnd, LB_GETTEXTLEN, dwSel, 0);
        TCHAR* pTexte = new TCHAR[(size) * sizeof(TCHAR)];
        SendMessage(hwnd, LB_GETTEXT, dwSel, (LPARAM)pTexte);
        size_t  count;
        char* pMBBuffer = new char[4000];

        count = wcstombs(pMBBuffer, pTexte, 4000);
        std::string texte(pMBBuffer);
        std::istringstream streamTexte(texte);
        std::string name, description;
        zrestmodel::ProjectRecord prj;
        std::getline(streamTexte, name, '|');
        std::getline(streamTexte, description, '|');
        std::getline(streamTexte, description, '|');
        prj.name = name;
        prj.description = description;
        prj.dele();
    
    }
}

LRESULT CALLBACK zrestgui::MainWindow::requestProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    MainWindow* pWindow = InstanceFromWndProc<MainWindow, MainWindow, &MainWindow::m_hWnd>(hwnd, uMsg, lParam);
    switch (uMsg)
    {
    case WM_COMMAND:

        // Test for the identifier of a command item. 

        switch (LOWORD(wParam))
        {
        case IDB_QUIT:
        case IDM_FQUIT:
            PostQuitMessage(0);   // application-defined 
            break;
        case IDB_NEW:
        case IDM_FNEW:
            DialogBox(NULL, MAKEINTRESOURCE(IDD_ADDPROJECT), hwnd, (DLGPROC)AddProjectProc);
            pWindow->afficheListe(GetDlgItem(hwnd, IDLB_MAINLISTBOX), hwnd);
            break;
        case IDB_DEL:
            pWindow->effaceSelection(GetDlgItem(hwnd, IDLB_MAINLISTBOX));
            pWindow->afficheListe(GetDlgItem(hwnd, IDLB_MAINLISTBOX), hwnd);
            break;
        case IDLB_MAINLISTBOX:
            switch (HIWORD(wParam))
            {
            case LBN_DBLCLK:
                RequestManager* p = new RequestManager(GetModuleHandle(NULL), hwnd);
                pWindow->pRequestManager.reset(p);
                break;
            }
            break;
        }

        break;

    case WM_DESTROY:
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);



        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
        pWindow->afficheListe(GetDlgItem(hwnd, IDLB_MAINLISTBOX), hwnd);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

zrestgui::MainWindow::~MainWindow()
{

}