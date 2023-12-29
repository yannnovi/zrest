#ifndef ZREST_MISC_HPP
#define ZREST_MISC_HPP
#include <log.hpp>
#include <languages.hpp>
#include <string>
#include <gtkmm.h>
namespace zrestlinuxutils
{
    template<typename T>
    void regSig(Glib::RefPtr<Gtk::Builder> builder,
                const std::string widgetName,
                Glib::SignalProxy<void> (T::*fp)(),
                Glib::SignalProxyProperty::SlotType &&callBack)
    {
        T *widget=0;
        builder->get_widget(widgetName, widget);
        if (widget)
        {
            (widget->*fp)().connect(callBack);
        }
        else
        {
	    char * msg=_("Could not get the Widget «{}».");
            zrestlog::Log::getInstance()->getLogger()->error(zrestlog::format(msg,widgetName));
        }
   }

   template<typename T>
   std::string getText(Glib::RefPtr<Gtk::Builder> builder,
                        const std::string widgetName)
    {
        std::string returnValue("BUG!");
        T *widget=0;
        builder->get_widget(widgetName, widget);
        if (widget)
        {
            returnValue = widget->get_buffer()->property_text().get_value().raw();
        }
        else
        {
            zrestlog::Log::getInstance()->getLogger()->error(zrestlog::format(_("Could not get the Widget «{}»."),widgetName));
        }
        return returnValue;

    }

    template<typename T>
    void clear(Glib::RefPtr<Gtk::Builder> builder,
                        const std::string widgetName)
    {
        T *widget=0;
        builder->get_widget(widgetName, widget);
        if (widget)
        {
            widget->get_buffer()->delete_text(0,-1);
        }
        else
        {
            zrestlog::Log::getInstance()->getLogger()->error(zrestlog::format(_("Could not get the Widget «{}»."),widgetName));
        }
  
    }

}

#endif
