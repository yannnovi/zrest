#ifndef ZREST_DB_HPP
#define ZREST_DB_HPP
#include "zrestdb.hpp"
#include <vector>
namespace zrestdb
{
class db 
{
    public:
        static db* getInstance();
        ~db();
        ZrestDB *getDb() {return dbh;}
        std::vector<zrestdb::Project> findAllProject();
        int generateId();
    private:
        db();

        ZrestDB *dbh;
};
}
#endif