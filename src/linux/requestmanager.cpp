#include "requestmanager.hpp"
#include "misc.hpp"

zrestguilinux::RequestManager::RequestManager(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
        Gtk::Window(cobject), _builder(builder),m_ListProjectViewText(2)
{
    zrestlinuxutils::regSig<Gtk::Button>(_builder,"RequestButQuitter",&Gtk::Button::signal_clicked,sigc::mem_fun(*this, &RequestManager::onQuit));
    set_position(Gtk::WIN_POS_CENTER);
    Gtk::Box *box;
    _builder->get_widget("RequestManagerBox", box);
    Gtk::Button *add;
    _builder->get_widget("RequestAddRequest", add);
     Gtk::Button *quit;
    _builder->get_widget("RequestButQuitter", quit);
     Gtk::Button *del;
    _builder->get_widget("RequestButtonDeleteRequest", del);

    add->set_size_request(180,32);
    quit->set_size_request(180,32);
    del->set_size_request(180,32);
    m_ScrolledWindow.add(m_ListProjectViewText);
    m_ScrolledWindow.set_size_request(990,768);

    m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    box->pack_start(m_ScrolledWindow);
    m_ListProjectViewText.set_column_title(0, "Requête");
    m_ListProjectViewText.set_column_title(1, "Description");
     box->set_size_request(80,32);
    box->pack_start(*add);
    box->pack_start(*del);
    box->pack_start(*quit);
    show_all_children();
}

zrestguilinux::RequestManager::~RequestManager()
{
}

void zrestguilinux::RequestManager::onQuit()
{
    hide();
}

void zrestguilinux::RequestManager::onAdd()
{
}

void zrestguilinux::RequestManager::onDelete()
{
}
