#ifndef REQUESTMANAGER_HPP
#define REQUESTMANAGER_HPP
#include "db.hpp"
#include "litesql.hpp"
#include "projectrecord.hpp"
#include <gtkmm.h>
namespace zrestguilinux
{
    class RequestManager : public Gtk::Window
    {

        public:
            RequestManager(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
            virtual ~RequestManager();
            inline void setParentProject(zrestmodel::ProjectRecord &prj)
            {
                parentProject = prj;
                this->set_title(prj.name.value());
            }

        protected:
            void onQuit();
            void onAdd();
            void onDelete();
             
        private:
            Glib::RefPtr<Gtk::Builder> _builder;
            Gtk::ListViewText m_ListProjectViewText;
            Gtk::ScrolledWindow m_ScrolledWindow;
            zrestmodel::ProjectRecord parentProject;
  };
}
#endif