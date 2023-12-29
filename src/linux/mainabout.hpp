#ifndef ZREST_MAINABOUT_HPP
#define ZREST_MAINABOUT_HPP

#include <gtkmm.h>
namespace zrestguilinux
{
class MainAbout : public Gtk::Dialog
{

public:
  MainAbout(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  virtual ~MainAbout();

protected:
  //Signal handlers:
   /** "quit" action handler. */
   void onOK();

private:
  Glib::RefPtr<Gtk::Builder> _builder;
};
}
#endif