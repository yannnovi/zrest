#ifndef ZREST_ADDPROJECT_HPP
#define ZREST_ADDPROJECT_HPP

#include <gtkmm.h>
namespace zrestguilinux
{
    class AddProject : public Gtk::Dialog
    {

        public:
            AddProject(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
            virtual ~AddProject();

        protected:
            void onAddProject();
            void onCancel();
        private:
            Glib::RefPtr<Gtk::Builder> _builder;
  };
}
#endif