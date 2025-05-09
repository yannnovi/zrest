// main.cpp
// (c)2021 ZorgulSoft
// By Yann Bourdeau
#include "log.hpp"
#include "db.hpp"
#include "languages.hpp"
#ifdef __linux
#include "main_gnome.hpp"
#endif
#ifdef __APPLE__
#include "main_darwin.h"
#endif
#include <iostream>
#include <ostream>
#ifdef WIN32
#include "main_win32.hpp"
#include <windows.h>
int WINAPI wWinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                    PWSTR lpCmdLine,
                   int nCmdShow)
{
    zrestlang::init_languages();
    zrestlog::Log::getInstance()->getLogger()->info(_("ZREST started."));
    
    zrestdb::db::getInstance();
    auto rc = zrestgui::main_app(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
    zrestlog::Log::getInstance()->getLogger()->info(_("ZREST ended."));
    return rc;

}
#else
int main(int argc,char ** argv)
{
    zrestlang::init_languages();
    zrestlog::Log::getInstance()->getLogger()->info(_("ZREST started."));
    zrestdb::db::getInstance();
    auto rc = zrestgui::main_app(argc,argv);
    zrestlog::Log::getInstance()->getLogger()->info(_("ZREST ended."));
    return rc;
}
#endif