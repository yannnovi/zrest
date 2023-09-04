#ifndef UNICODE
#define UNICODE
#endif 

#include "main_win32.hpp"
#include "mainwindow.hpp"
#include <windows.h>




int WINAPI zrestgui::main_app(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    MainWindow win(hInstance, 0, nCmdShow);
    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
