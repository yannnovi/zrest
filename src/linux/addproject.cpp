#include "addproject.hpp"
#include "languages.hpp"
#include "projectrecord.hpp"
#include "misc.hpp"
#include "mainwindow.hpp"
#include "widgetlocale.hpp"
#include "db.hpp"
#include <gtkmm.h>

zrestguilinux::AddProject::AddProject(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
        Gtk::Dialog(cobject), _builder(builder)
{
    
    zrestlinuxutils::regSig<Gtk::Button>(_builder,"AddProjectCancelButton",&Gtk::Button::signal_clicked,sigc::mem_fun(*this, &AddProject::onCancel));
    zrestlinuxutils::regSig<Gtk::Button>(_builder,"AddProjectButton",&Gtk::Button::signal_clicked,sigc::mem_fun(*this, &AddProject::onAddProject));
}

zrestguilinux::AddProject::~AddProject()
{
}
void zrestguilinux::AddProject::onAddProject()
{
    zrestmodel::ProjectRecord prj;
    prj.id = zrestdb::db::getInstance()->generateId(); 
    prj.name = zrestlinuxutils::getText<Gtk::Entry>(_builder,"AddProjectProject");
    prj.description = zrestlinuxutils::getText<Gtk::Entry>(_builder,"AddProjectDescription");
    if(!prj.name.value().empty())
    {
        prj.save();
    }
    
    zrestlinuxutils::clear<Gtk::Entry>(_builder,"AddProjectProject");
    zrestlinuxutils::clear<Gtk::Entry>(_builder,"AddProjectDescription");
    hide();
}

void zrestguilinux::AddProject::onCancel()
{
    zrestlinuxutils::clear<Gtk::Entry>(_builder,"AddProjectProject");
    zrestlinuxutils::clear<Gtk::Entry>(_builder,"AddProjectDescription");
    hide();
}