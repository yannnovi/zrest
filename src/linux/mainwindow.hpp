#ifndef ZREST_MAINWINDOW_H
#define ZREST_MAINWINDOW_H
#include "mainabout.hpp"
#include <gtkmm.h>
namespace zrestguilinux
{
class MainWindow : public Gtk::Window
{

public:
  MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  virtual ~MainWindow();
  void afficheProjet();
protected:
  //Signal handlers:
   /** "quit" action handler. */
   void onQuit();
   void aboutMenu();
   void onAdd();
   void onShow();
   void onDelete(); 
   void onListBoxRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
private:
    Glib::RefPtr<Gtk::Builder> _builder;
    MainAbout * _pMainAbout;
    Gtk::ListViewText m_ListProjectViewText;
    Gtk::ScrolledWindow m_ScrolledWindow;

};
}
#endif
