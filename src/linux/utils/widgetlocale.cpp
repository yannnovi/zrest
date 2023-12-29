#include "widgetlocale.hpp"
#include "languages.hpp"
#include "csv.h"
#include <gtkmm.h>
#include <fmt/core.h>
#include <string>
#include <iostream>
 
// the idea of using an hash to do a switch on string and the two following functins was taken from : https://learnmoderncpp.com/2020/06/01/strings-as-switch-case-labels/
constexpr inline auto string_hash(const char *s) {
    unsigned long long hash{}, c{};
    for (auto p = s; *p; ++p, ++c) {
        hash += *p << c;
    }
    return hash;
}
 
constexpr inline auto operator"" _sh(const char *s, size_t) {
    return string_hash(s);
}

int zrestguilinuxutils::loadLocaleWidget(std::string name,const Glib::RefPtr<Gtk::Builder>& builder)
{
    io::CSVReader<3> in(fmt::format("locale/linux/{}.csv",name));
    //widget_type,name,msgid
    in.read_header(io::ignore_extra_column, "widget_type", "name", "msgid");
    std::string type; std::string widget_name; std::string msgid;
    while(in.read_row(type, widget_name, msgid)){
        switch(string_hash(type.c_str()))
        {
            case "button"_sh:
                Gtk::Button *button;
                builder->get_widget(widget_name.c_str(), button);
                button->set_label(_(msgid.c_str()));
            break;

        }
    }
    return 0;
} 