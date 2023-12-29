#ifndef ZREST_PROJECTRECORD_HPP
#define ZREST_PROJECTRECORD_HPP
#include "zrestdb.hpp"
namespace zrestmodel
{
    class ProjectRecord : public zrestdb::Project
    {
        public:
            ProjectRecord();
            void save();
            void dele();
            virtual ~ProjectRecord();
    };
}

#endif