#include "main_gnome.hpp"
#include "widgetlocale.hpp"
#include "languages.hpp"
#include "log.hpp"
#include "mainwindow.hpp"
#include <gtkmm.h>
#include <iostream>

namespace
{
zrestguilinux::MainWindow* pMainWindow = nullptr;
Glib::RefPtr<Gtk::Application> app;

void on_app_activate()
{
    // Load the GtkBuilder file and instantiate its widgets:
    auto refBuilder = Gtk::Builder::create();
    try
    {
      refBuilder->add_from_file("glade/zrest.glade");
    }
    catch(const Glib::FileError& ex)
    {
      zrestlog::Log::getInstance()->getLogger()->error("FileError: {}",ex.what().raw());
      return;
    }
    catch(const Glib::MarkupError& ex)
    {
      zrestlog::Log::getInstance()->getLogger()->error("MarkupError: {}",ex.what().raw());
      return;
    }
    catch(const Gtk::BuilderError& ex)
    {
      zrestlog::Log::getInstance()->getLogger()->error("BuilderError: {}",ex.what().raw());
      return;
    }

    // Get the GtkBuilder-instantiated dialog:
    //refBuilder->get_widget<Gtk::Window>("MainWindow",pMainWindow);
    
    
    refBuilder->get_widget_derived("MainWindow", pMainWindow);
    if (!pMainWindow)
    {
      zrestlog::Log::getInstance()->getLogger()->error(_("Could not get the Windows."));
      return;
    }
  
    app->add_window(*pMainWindow);
    zrestguilinuxutils::loadLocaleWidget("mainwindows",refBuilder);

    pMainWindow->show();
    zrestguilinuxutils::loadLocaleWidget("mainabout",refBuilder);
    zrestguilinuxutils::loadLocaleWidget("addproject",refBuilder);
    zrestguilinuxutils::loadLocaleWidget("requestmanager",refBuilder);

}
} // anonymous namespace


int zrestgui::main_app(int argc, char *argv[])
{
    app = Gtk::Application::create(argc, argv, "ca.zorgulsoft.zrest");

    app->signal_activate().connect([] () { on_app_activate(); });

    app->run(argc, argv);


  return 0;
}