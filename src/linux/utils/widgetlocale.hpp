#ifndef ZREST_WIDGETLOCALE_HPP
#define ZREST_WIDGETLOCALE_HPP
#include <gtkmm.h>
#include <string>
namespace zrestguilinuxutils
{
int loadLocaleWidget(std::string name,const Glib::RefPtr<Gtk::Builder>& builder);
}
#endif