#include "mainabout.hpp"
#include "misc.hpp"
#include "languages.hpp"
#include <gtkmm.h>

zrestguilinux::MainAbout::MainAbout(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
        Gtk::Dialog(cobject), _builder(builder)
{
    zrestlinuxutils::regSig<Gtk::Button>(_builder,"AboutOK",&Gtk::Button::signal_clicked,sigc::mem_fun(*this, &MainAbout::onOK));

 }

zrestguilinux::MainAbout::~MainAbout()
{
}

void zrestguilinux::MainAbout::onOK()
{
    hide();
}
