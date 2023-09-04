#include "mainwindow.hpp"
#include "misc.hpp"
#include "mainabout.hpp"
#include "addproject.hpp"
#include "languages.hpp"
#include "db.hpp"
#include "litesql.hpp"
#include "projectrecord.hpp"
#include "requestmanager.hpp"
#include <iostream>
#include <vector>
zrestguilinux::MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
        Gtk::Window(cobject), _builder(builder), m_ListProjectViewText(2)
{
    zrestlinuxutils::regSig<Gtk::MenuItem>(_builder,"QuitMenu",&Gtk::MenuItem::signal_activate,sigc::mem_fun(*this, &MainWindow::onQuit));
    zrestlinuxutils::regSig<Gtk::MenuItem>(_builder,"AboutMenu",&Gtk::MenuItem::signal_activate,sigc::mem_fun(*this, &MainWindow::aboutMenu));
    zrestlinuxutils::regSig<Gtk::MenuItem>(_builder,"NewMenu",&Gtk::MenuItem::signal_activate,sigc::mem_fun(*this, &MainWindow::onAdd));
    zrestlinuxutils::regSig<Gtk::Button>(_builder,"MainAddProject",&Gtk::Button::signal_clicked,sigc::mem_fun(*this, &MainWindow::onAdd));
    zrestlinuxutils::regSig<Gtk::Button>(_builder,"MainButQuitter",&Gtk::Button::signal_clicked,sigc::mem_fun(*this, &MainWindow::onQuit));
    zrestlinuxutils::regSig<Gtk::Button>(_builder,"MainButtonDeleteProject",&Gtk::Button::signal_clicked,sigc::mem_fun(*this, &MainWindow::onDelete));
 
    m_ListProjectViewText.signal_row_activated().connect(sigc::mem_fun(*this, &MainWindow::onListBoxRowActivated) );

    set_position(Gtk::WIN_POS_CENTER);
    _builder->get_widget_derived("MainAbout", _pMainAbout);


    m_ScrolledWindow.add(m_ListProjectViewText);
    m_ScrolledWindow.set_size_request(990,768);

    m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    Gtk::Box *box;
    _builder->get_widget("MainBox", box);
    Gtk::Button *add;
    _builder->get_widget("MainAddProject", add);
     Gtk::Button *quit;
    _builder->get_widget("MainButQuitter", quit);
     Gtk::Button *del;
    _builder->get_widget("MainButtonDeleteProject", del);

    add->set_size_request(180,32);
    quit->set_size_request(180,32);
    del->set_size_request(180,32);
    box->pack_start(m_ScrolledWindow);
    box->set_size_request(80,32);
    box->pack_start(*add);
    box->pack_start(*del);
    box->pack_start(*quit);
     //Fill the ListViewText:
    m_ListProjectViewText.set_column_title(0, "Projet");
    m_ListProjectViewText.set_column_title(1, "Description");
    afficheProjet();
    show_all_children();
}
    

zrestguilinux::MainWindow::~MainWindow()
{
}

void zrestguilinux::MainWindow::onListBoxRowActivated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column)
{
    const auto list = m_ListProjectViewText.get_selected();
    auto index=list.begin();
    if (index != list.end())
    {   
        zrestmodel::ProjectRecord prj;
        prj.name = m_ListProjectViewText.get_text(*index,0).operator std::string();
        prj.description = m_ListProjectViewText.get_text(*index,1).operator std::string();
    
        RequestManager *window=0;
        _builder->get_widget_derived("RequestManager", window);
        window->setParentProject(prj);
        window->show_all();

    }
}
void zrestguilinux::MainWindow::onQuit()
{
    hide();
}

void zrestguilinux::MainWindow::onAdd()
{
     AddProject *dlg=0;
    _builder->get_widget_derived("AddProject", dlg);
    dlg->run();
    afficheProjet();
}

void zrestguilinux::MainWindow::onDelete()
{
    auto vIndex=m_ListProjectViewText.get_selected();
    for( auto index=vIndex.begin();index!=vIndex.end();++index)
    {
        zrestmodel::ProjectRecord prj;
        prj.name = m_ListProjectViewText.get_text(*index,0).operator std::string();
        prj.description = m_ListProjectViewText.get_text(*index,1).operator std::string();
        prj.dele();
    }
    afficheProjet();
}



void zrestguilinux::MainWindow::aboutMenu()
{
   _pMainAbout->run();
}

void zrestguilinux::MainWindow::afficheProjet() 
{
    m_ListProjectViewText.clear_items();
    auto  liste_projets = zrestdb::db::getInstance()->findAllProject();
    //MainCollectionsList
    for (auto  &projet : liste_projets)
    {
        guint row_number = m_ListProjectViewText.append();
        m_ListProjectViewText.set_text(row_number, 0, projet.name.value());
        m_ListProjectViewText.set_text(row_number, 1, projet.description.value());   
    }

}
