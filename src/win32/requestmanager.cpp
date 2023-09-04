#ifndef UNICODE
#define UNICODE
#endif 
#include "requestmanager.hpp"
#include "log.hpp"
#include "languages.hpp"
#include "instancewnd.hpp"
#include <windows.h>
#include <atlbase.h>
#define IDB_QUIT 3001
#define IDB_NEW  3002
#define IDLB_MAINLISTBOX 3003
#define IDB_DEL 3004


zrestgui::RequestManager::RequestManager(HINSTANCE hInstance,HWND parent)
{
    auto log = zrestlog::Log::getInstance()->getLogger();

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"ZRest Request Manager";

    WNDCLASS wc = { };

    wc.lpfnWndProc = requestProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Requests Manager",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        parent,       // Parent window    
        NULL,       // Menu
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

    ShowWindow(hwnd, 1);

}

LRESULT CALLBACK zrestgui::RequestManager::requestProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RequestManager* pWindow = InstanceFromWndProc<RequestManager, RequestManager, &RequestManager::m_hWnd>(hwnd, uMsg, lParam);
    switch (uMsg)
    {
    case WM_COMMAND:

        // Test for the identifier of a command item. 

        switch (LOWORD(wParam))
        {
        case IDB_QUIT:
            DestroyWindow(hwnd);   // application-defined 
            break;
        case IDB_NEW:
            break;
        case IDB_DEL:
            break;
        case IDLB_MAINLISTBOX:
            switch (HIWORD(wParam))
            {
            case LBN_DBLCLK:
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
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

zrestgui::RequestManager::~RequestManager()
{

}