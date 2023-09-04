#include "db.hpp"
#include "zrestdb.hpp"
void zrestdb::user::sayHello() {
    std::cout << "Hi! My name is " << name << std::endl;
}


zrestdb::db::db()
{
    dbh = new zrestdb::ZrestDB("sqlite3", "database=zrestdb.db");
    dbh->verbose = true;
 
    if (dbh->needsUpgrade())
    {
      dbh->upgrade();
    }

}

std::vector<zrestdb::Project> zrestdb::db::findAllProject()
{
  return  select<zrestdb::Project>(*(getDb())).all();
}

zrestdb::db::~db()
{
    delete dbh;
}
static zrestdb::db* gInstance=0;

zrestdb::db * zrestdb::db::getInstance()
{
    if(!gInstance)
    {
        gInstance = new db();
    }
    return gInstance;
}
int zrestdb::db::generateId()
{
    int id =1;
    dbh->begin();
        
    try {
       auto oldRec= litesql::select<zrestdb::idgen>(*dbh, zrestdb::idgen::Id == 1).one();
       id=oldRec.idgenenarator;
       oldRec.idgenenarator=++id;
       oldRec.del();
       oldRec.update();
    } catch (litesql::NotFound e) {
        zrestdb::idgen rec(*dbh);
        rec.id=1;
        rec.idgenenarator=1;
        rec.update();
 
    }
    dbh->commit();
 
    return id;
}