#include "zrestdb.hpp"
namespace zrestdb {
using namespace litesql;
ProjectRequestRelation::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : request(ProjectRequestRelation::Request), project(ProjectRequestRelation::Project) {
    switch(rec.size()) {
    case 2:
        request = rec[1];
    case 1:
        project = rec[0];
    }
}
const std::string ProjectRequestRelation::table__("Project_Request_");
const litesql::FieldType ProjectRequestRelation::Project("Project1_",A_field_type_integer,table__);
const litesql::FieldType ProjectRequestRelation::Request("Request2_",A_field_type_integer,table__);
void ProjectRequestRelation::link(const litesql::Database& db, const zrestdb::Project& o0, const zrestdb::Request& o1) {
    Record values;
    Split fields;
    fields.push_back(Project.name());
    values.push_back(o0.id);
    fields.push_back(Request.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void ProjectRequestRelation::unlink(const litesql::Database& db, const zrestdb::Project& o0, const zrestdb::Request& o1) {
    db.delete_(table__, (Project == o0.id && Request == o1.id));
}
void ProjectRequestRelation::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<ProjectRequestRelation::Row> ProjectRequestRelation::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Project.fullName());
    sel.result(Request.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<ProjectRequestRelation::Row>(db, sel);
}
template <> litesql::DataSource<zrestdb::Project> ProjectRequestRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Project.fullName());
    sel.where(srcExpr);
    return DataSource<zrestdb::Project>(db, zrestdb::Project::Id.in(sel) && expr);
}
template <> litesql::DataSource<zrestdb::Request> ProjectRequestRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Request.fullName());
    sel.where(srcExpr);
    return DataSource<zrestdb::Request>(db, zrestdb::Request::Id.in(sel) && expr);
}
const litesql::FieldType user::Own::Id("id_",A_field_type_integer,"user_");
const std::string user::type__("user");
const std::string user::table__("user_");
const std::string user::sequence__("user_seq");
const litesql::FieldType user::Id("id_",A_field_type_integer,table__);
const litesql::FieldType user::Type("type_",A_field_type_string,table__);
const litesql::FieldType user::Name("name_",A_field_type_string,table__);
const litesql::FieldType user::Passwd("passwd_",A_field_type_string,table__);
void user::initValues() {
}
void user::defaults() {
    id = 0;
}
user::user(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), name(Name), passwd(Passwd) {
    defaults();
}
user::user(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), name(Name), passwd(Passwd) {
    defaults();
    size_t size = (rec.size() > 4) ? 4 : rec.size();
    switch(size) {
    case 4: passwd = convert<const std::string&, std::string>(rec[3]);
        passwd.setModified(false);
    case 3: name = convert<const std::string&, std::string>(rec[2]);
        name.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
user::user(const user& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), name(obj.name), passwd(obj.passwd) {
}
const user& user::operator=(const user& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        name = obj.name;
        passwd = obj.passwd;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string user::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fields.push_back(passwd.name());
    values.push_back(passwd);
    passwd.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void user::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void user::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, name);
    updateField(updates, table__, passwd);
}
void user::addIDUpdates(Updates& updates) {
}
void user::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Name);
    ftypes.push_back(Passwd);
}
void user::delRecord() {
    deleteFromTable(table__, id);
}
void user::delRelations() {
}
void user::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void user::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<user> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool user::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<user> user::upcast() const {
    return unique_ptr<user>(new user(*this));
}
std::unique_ptr<user> user::upcastCopy() const {
    user* np = new user(*this);
    np->id = id;
    np->type = type;
    np->name = name;
    np->passwd = passwd;
    np->inDatabase = inDatabase;
    return unique_ptr<user>(np);
}
std::ostream & operator<<(std::ostream& os, user o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << o.passwd.name() << " = " << o.passwd << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Project::Own::Id("id_",A_field_type_integer,"Project_");
Project::RequestsHandle::RequestsHandle(const Project& owner)
         : litesql::RelationHandle<Project>(owner) {
}
void Project::RequestsHandle::link(const Request& o0) {
    ProjectRequestRelation::link(owner->getDatabase(), *owner, o0);
}
void Project::RequestsHandle::unlink(const Request& o0) {
    ProjectRequestRelation::unlink(owner->getDatabase(), *owner, o0);
}
void Project::RequestsHandle::del(const litesql::Expr& expr) {
    ProjectRequestRelation::del(owner->getDatabase(), expr && ProjectRequestRelation::Project == owner->id);
}
litesql::DataSource<Request> Project::RequestsHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return ProjectRequestRelation::get<Request>(owner->getDatabase(), expr, (ProjectRequestRelation::Project == owner->id) && srcExpr);
}
litesql::DataSource<ProjectRequestRelation::Row> Project::RequestsHandle::getRows(const litesql::Expr& expr) {
    return ProjectRequestRelation::getRows(owner->getDatabase(), expr && (ProjectRequestRelation::Project == owner->id));
}
const std::string Project::type__("Project");
const std::string Project::table__("Project_");
const std::string Project::sequence__("Project_seq");
const litesql::FieldType Project::Id("id_",A_field_type_integer,table__);
const litesql::FieldType Project::Type("type_",A_field_type_string,table__);
const litesql::FieldType Project::Name("name_",A_field_type_string,table__);
const litesql::FieldType Project::Description("description_",A_field_type_string,table__);
void Project::initValues() {
}
void Project::defaults() {
    id = 0;
}
Project::Project(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), name(Name), description(Description) {
    defaults();
}
Project::Project(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), name(Name), description(Description) {
    defaults();
    size_t size = (rec.size() > 4) ? 4 : rec.size();
    switch(size) {
    case 4: description = convert<const std::string&, std::string>(rec[3]);
        description.setModified(false);
    case 3: name = convert<const std::string&, std::string>(rec[2]);
        name.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Project::Project(const Project& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), name(obj.name), description(obj.description) {
}
const Project& Project::operator=(const Project& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        name = obj.name;
        description = obj.description;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
Project::RequestsHandle Project::requests() {
    return Project::RequestsHandle(*this);
}
std::string Project::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fields.push_back(description.name());
    values.push_back(description);
    description.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Project::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Project::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, name);
    updateField(updates, table__, description);
}
void Project::addIDUpdates(Updates& updates) {
}
void Project::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Name);
    ftypes.push_back(Description);
}
void Project::delRecord() {
    deleteFromTable(table__, id);
}
void Project::delRelations() {
    ProjectRequestRelation::del(*db, (ProjectRequestRelation::Project == id));
}
void Project::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Project::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<Project> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Project::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<Project> Project::upcast() const {
    return unique_ptr<Project>(new Project(*this));
}
std::unique_ptr<Project> Project::upcastCopy() const {
    Project* np = new Project(*this);
    np->id = id;
    np->type = type;
    np->name = name;
    np->description = description;
    np->inDatabase = inDatabase;
    return unique_ptr<Project>(np);
}
std::ostream & operator<<(std::ostream& os, Project o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << o.description.name() << " = " << o.description << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType idgen::Own::Id("id_",A_field_type_integer,"idgen_");
const std::string idgen::type__("idgen");
const std::string idgen::table__("idgen_");
const std::string idgen::sequence__("idgen_seq");
const litesql::FieldType idgen::Id("id_",A_field_type_integer,table__);
const litesql::FieldType idgen::Type("type_",A_field_type_string,table__);
const litesql::FieldType idgen::Idgenenarator("idgenenarator_",A_field_type_integer,table__);
void idgen::initValues() {
}
void idgen::defaults() {
    id = 0;
    idgenenarator = 1;
}
idgen::idgen(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), idgenenarator(Idgenenarator) {
    defaults();
}
idgen::idgen(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), idgenenarator(Idgenenarator) {
    defaults();
    size_t size = (rec.size() > 3) ? 3 : rec.size();
    switch(size) {
    case 3: idgenenarator = convert<const std::string&, int>(rec[2]);
        idgenenarator.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
idgen::idgen(const idgen& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), idgenenarator(obj.idgenenarator) {
}
const idgen& idgen::operator=(const idgen& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        idgenenarator = obj.idgenenarator;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string idgen::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(idgenenarator.name());
    values.push_back(idgenenarator);
    idgenenarator.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void idgen::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void idgen::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, idgenenarator);
}
void idgen::addIDUpdates(Updates& updates) {
}
void idgen::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Idgenenarator);
}
void idgen::delRecord() {
    deleteFromTable(table__, id);
}
void idgen::delRelations() {
}
void idgen::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void idgen::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<idgen> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool idgen::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<idgen> idgen::upcast() const {
    return unique_ptr<idgen>(new idgen(*this));
}
std::unique_ptr<idgen> idgen::upcastCopy() const {
    idgen* np = new idgen(*this);
    np->id = id;
    np->type = type;
    np->idgenenarator = idgenenarator;
    np->inDatabase = inDatabase;
    return unique_ptr<idgen>(np);
}
std::ostream & operator<<(std::ostream& os, idgen o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.idgenenarator.name() << " = " << o.idgenenarator << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Request::Own::Id("id_",A_field_type_integer,"Request_");
const int Request::BodyFormatType::json(0);
const int Request::BodyFormatType::xml(1);
Request::BodyFormatType::BodyFormatType(const std::string& n, AT_field_type t, const std::string& tbl, const litesql::FieldType::Values& vals)
         : litesql::FieldType(n,t,tbl,vals) {
}
const int Request::BodyFormat::json(0);
const int Request::BodyFormat::xml(1);
Request::ProjectHandle::ProjectHandle(const Request& owner)
         : litesql::RelationHandle<Request>(owner) {
}
void Request::ProjectHandle::link(const Project& o0) {
    ProjectRequestRelation::link(owner->getDatabase(), o0, *owner);
}
void Request::ProjectHandle::unlink(const Project& o0) {
    ProjectRequestRelation::unlink(owner->getDatabase(), o0, *owner);
}
void Request::ProjectHandle::del(const litesql::Expr& expr) {
    ProjectRequestRelation::del(owner->getDatabase(), expr && ProjectRequestRelation::Request == owner->id);
}
litesql::DataSource<Project> Request::ProjectHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return ProjectRequestRelation::get<Project>(owner->getDatabase(), expr, (ProjectRequestRelation::Request == owner->id) && srcExpr);
}
litesql::DataSource<ProjectRequestRelation::Row> Request::ProjectHandle::getRows(const litesql::Expr& expr) {
    return ProjectRequestRelation::getRows(owner->getDatabase(), expr && (ProjectRequestRelation::Request == owner->id));
}
const std::string Request::type__("Request");
const std::string Request::table__("Request_");
const std::string Request::sequence__("Request_seq");
const litesql::FieldType Request::Id("id_",A_field_type_integer,table__);
const litesql::FieldType Request::Type("type_",A_field_type_string,table__);
const litesql::FieldType Request::Name("name_",A_field_type_string,table__);
const litesql::FieldType Request::Description("description_",A_field_type_string,table__);
const litesql::FieldType Request::Body("body_",A_field_type_blob,table__);
std::vector < std::pair< std::string, std::string > > Request::bodyFormat_values;
const litesql::FieldType Request::BodyFormat("bodyFormat_",A_field_type_integer,table__);
const litesql::FieldType Request::Secure("secure_",A_field_type_boolean,table__);
void Request::initValues() {
    bodyFormat_values.clear();
    bodyFormat_values.push_back(make_pair<std::string, std::string>("json","0"));
    bodyFormat_values.push_back(make_pair<std::string, std::string>("xml","1"));
}
void Request::defaults() {
    id = 0;
    body = Blob();
    bodyFormat = 0;
    secure = 0;
}
Request::Request(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), name(Name), description(Description), body(Body), bodyFormat(BodyFormat), secure(Secure) {
    defaults();
}
Request::Request(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), name(Name), description(Description), body(Body), bodyFormat(BodyFormat), secure(Secure) {
    defaults();
    size_t size = (rec.size() > 7) ? 7 : rec.size();
    switch(size) {
    case 7: secure = convert<const std::string&, bool>(rec[6]);
        secure.setModified(false);
    case 6: bodyFormat = convert<const std::string&, int>(rec[5]);
        bodyFormat.setModified(false);
    case 5: body = convert<const std::string&, litesql::Blob>(rec[4]);
        body.setModified(false);
    case 4: description = convert<const std::string&, std::string>(rec[3]);
        description.setModified(false);
    case 3: name = convert<const std::string&, std::string>(rec[2]);
        name.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Request::Request(const Request& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), name(obj.name), description(obj.description), body(obj.body), bodyFormat(obj.bodyFormat), secure(obj.secure) {
}
const Request& Request::operator=(const Request& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        name = obj.name;
        description = obj.description;
        body = obj.body;
        bodyFormat = obj.bodyFormat;
        secure = obj.secure;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
Request::ProjectHandle Request::project() {
    return Request::ProjectHandle(*this);
}
std::string Request::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fields.push_back(description.name());
    values.push_back(description);
    description.setModified(false);
    fields.push_back(body.name());
    values.push_back(body);
    body.setModified(false);
    fields.push_back(bodyFormat.name());
    values.push_back(bodyFormat);
    bodyFormat.setModified(false);
    fields.push_back(secure.name());
    values.push_back(secure);
    secure.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Request::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Request::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, name);
    updateField(updates, table__, description);
    updateField(updates, table__, body);
    updateField(updates, table__, bodyFormat);
    updateField(updates, table__, secure);
}
void Request::addIDUpdates(Updates& updates) {
}
void Request::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Name);
    ftypes.push_back(Description);
    ftypes.push_back(Body);
    ftypes.push_back(BodyFormat);
    ftypes.push_back(Secure);
}
void Request::delRecord() {
    deleteFromTable(table__, id);
}
void Request::delRelations() {
    ProjectRequestRelation::del(*db, (ProjectRequestRelation::Request == id));
}
void Request::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Request::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<Request> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Request::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<Request> Request::upcast() const {
    return unique_ptr<Request>(new Request(*this));
}
std::unique_ptr<Request> Request::upcastCopy() const {
    Request* np = new Request(*this);
    np->id = id;
    np->type = type;
    np->name = name;
    np->description = description;
    np->body = body;
    np->bodyFormat = bodyFormat;
    np->secure = secure;
    np->inDatabase = inDatabase;
    return unique_ptr<Request>(np);
}
std::ostream & operator<<(std::ostream& os, Request o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << o.description.name() << " = " << o.description << std::endl;
    os << o.body.name() << " = " << o.body << std::endl;
    os << o.bodyFormat.name() << " = " << o.bodyFormat << std::endl;
    os << o.secure.name() << " = " << o.secure << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
ZrestDB::ZrestDB(std::string backendType, std::string connInfo)
     : litesql::Database(backendType, connInfo) {
    initialize();
}
std::vector<litesql::Database::SchemaItem> ZrestDB::getSchema() const {
    vector<Database::SchemaItem> res;
    string TEXT = backend->getSQLType(A_field_type_string);
    string rowIdType = backend->getRowIDType();
    res.push_back(Database::SchemaItem("schema_","table","CREATE TABLE schema_ (name_ "+TEXT+", type_ "+TEXT+", sql_ "+TEXT+")"));
    if (backend->supportsSequences()) {
        res.push_back(Database::SchemaItem("user_seq","sequence",backend->getCreateSequenceSQL("user_seq")));
        res.push_back(Database::SchemaItem("Project_seq","sequence",backend->getCreateSequenceSQL("Project_seq")));
        res.push_back(Database::SchemaItem("idgen_seq","sequence",backend->getCreateSequenceSQL("idgen_seq")));
        res.push_back(Database::SchemaItem("Request_seq","sequence",backend->getCreateSequenceSQL("Request_seq")));
    }
    res.push_back(Database::SchemaItem("user_","table","CREATE TABLE user_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",name_ " + backend->getSQLType(A_field_type_string,"256") + "" +",passwd_ " + backend->getSQLType(A_field_type_string,"") + "" +")"));
    res.push_back(Database::SchemaItem("Project_","table","CREATE TABLE Project_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",name_ " + backend->getSQLType(A_field_type_string,"50") + "" +",description_ " + backend->getSQLType(A_field_type_string,"256") + "" +")"));
    res.push_back(Database::SchemaItem("idgen_","table","CREATE TABLE idgen_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",idgenenarator_ " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("Request_","table","CREATE TABLE Request_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",name_ " + backend->getSQLType(A_field_type_string,"50") + "" +",description_ " + backend->getSQLType(A_field_type_string,"256") + "" +",body_ " + backend->getSQLType(A_field_type_blob,"") + "" +",bodyFormat_ " + backend->getSQLType(A_field_type_integer,"") + "" +",secure_ " + backend->getSQLType(A_field_type_boolean,"") + "" +")"));
    res.push_back(Database::SchemaItem("Project_Request_","table","CREATE TABLE Project_Request_ (Project1_ " + backend->getSQLType(A_field_type_integer,"") + "" +",Request2_ " + backend->getSQLType(A_field_type_integer,"") + " UNIQUE" +")"));
    res.push_back(Database::SchemaItem("user_id_idx","index","CREATE INDEX user_id_idx ON user_ (id_)"));
    res.push_back(Database::SchemaItem("Project_id_idx","index","CREATE INDEX Project_id_idx ON Project_ (id_)"));
    res.push_back(Database::SchemaItem("Project__name_idx","index","CREATE UNIQUE INDEX Project__name_idx ON Project_ (name_)"));
    res.push_back(Database::SchemaItem("idgen_id_idx","index","CREATE INDEX idgen_id_idx ON idgen_ (id_)"));
    res.push_back(Database::SchemaItem("Request_id_idx","index","CREATE INDEX Request_id_idx ON Request_ (id_)"));
    res.push_back(Database::SchemaItem("Project_Request_Project1_idx","index","CREATE INDEX Project_Request_Project1_idx ON Project_Request_ (Project1_)"));
    res.push_back(Database::SchemaItem("Project_Request_Request2_idx","index","CREATE INDEX Project_Request_Request2_idx ON Project_Request_ (Request2_)"));
    res.push_back(Database::SchemaItem("Project_Request__all_idx","index","CREATE INDEX Project_Request__all_idx ON Project_Request_ (Project1_,Request2_)"));
    return res;
}
void ZrestDB::initialize() {
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;
    Request::initValues();
}
}
