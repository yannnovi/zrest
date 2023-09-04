#include "projectrecord.hpp"
#include "db.hpp"
#include "zrestdb.hpp"

zrestmodel::ProjectRecord::ProjectRecord():Project(*zrestdb::db::getInstance()->getDb())
{

}
zrestmodel::ProjectRecord::~ProjectRecord()
{
    
}
void zrestmodel::ProjectRecord::save()
{
    auto db = zrestdb::db::getInstance()->getDb();
    db->begin();
    update();
    db->commit();
}

void zrestmodel::ProjectRecord::dele()
{
    auto db = zrestdb::db::getInstance()->getDb();
    try {
        std::string name=this->name;
        auto rec= litesql::select<zrestdb::Project>(*db, (zrestdb::Project::Name == name)).one();
        rec.del();
    } catch (litesql::NotFound e) {
        //noop
    }
}