#ifndef zrestdb_hpp
#define zrestdb_hpp
#include "litesql.hpp"
namespace zrestdb {
class user;
class Project;
class idgen;
class Request;
class ProjectRequestRelation {
public:
    class Row {
    public:
        litesql::Field<int> request;
        litesql::Field<int> project;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Project;
    static const litesql::FieldType Request;
    static void link(const litesql::Database& db, const zrestdb::Project& o0, const zrestdb::Request& o1);
    static void unlink(const litesql::Database& db, const zrestdb::Project& o0, const zrestdb::Request& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<ProjectRequestRelation::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
;
;
};
class user : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static const litesql::FieldType Passwd;
    litesql::Field<std::string> passwd;
    static void initValues();
protected:
    void defaults();
public:
    user(const litesql::Database& db);
    user(const litesql::Database& db, const litesql::Record& rec);
    user(const user& obj);
    const user& operator=(const user& obj);
    virtual void sayHello();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::unique_ptr<user> upcast() const;
    std::unique_ptr<user> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, user o);
class Project : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class RequestsHandle : public litesql::RelationHandle<Project> {
    public:
        RequestsHandle(const Project& owner);
        void link(const Request& o0);
        void unlink(const Request& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Request> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<ProjectRequestRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static const litesql::FieldType Description;
    litesql::Field<std::string> description;
    static void initValues();
protected:
    void defaults();
public:
    Project(const litesql::Database& db);
    Project(const litesql::Database& db, const litesql::Record& rec);
    Project(const Project& obj);
    const Project& operator=(const Project& obj);
    Project::RequestsHandle requests();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::unique_ptr<Project> upcast() const;
    std::unique_ptr<Project> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Project o);
class idgen : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Idgenenarator;
    litesql::Field<int> idgenenarator;
    static void initValues();
protected:
    void defaults();
public:
    idgen(const litesql::Database& db);
    idgen(const litesql::Database& db, const litesql::Record& rec);
    idgen(const idgen& obj);
    const idgen& operator=(const idgen& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::unique_ptr<idgen> upcast() const;
    std::unique_ptr<idgen> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, idgen o);
class Request : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class BodyFormatType : public litesql::FieldType {
    public:
        static const int json;
        static const int xml;
        BodyFormatType(const std::string& n, AT_field_type t, const std::string& tbl, const litesql::FieldType::Values& vals=Values());
    };
    class BodyFormat {
    public:
        static const int json;
        static const int xml;
    };
    class ProjectHandle : public litesql::RelationHandle<Request> {
    public:
        ProjectHandle(const Request& owner);
        void link(const Project& o0);
        void unlink(const Project& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Project> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<ProjectRequestRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static const litesql::FieldType Description;
    litesql::Field<std::string> description;
    static const litesql::FieldType Body;
    litesql::Field<litesql::Blob> body;
protected:
    static std::vector < std::pair< std::string, std::string > > bodyFormat_values;
public:
    static const litesql::FieldType BodyFormat;
    litesql::Field<int> bodyFormat;
    static const litesql::FieldType Secure;
    litesql::Field<bool> secure;
    static void initValues();
protected:
    void defaults();
public:
    Request(const litesql::Database& db);
    Request(const litesql::Database& db, const litesql::Record& rec);
    Request(const Request& obj);
    const Request& operator=(const Request& obj);
    Request::ProjectHandle project();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::unique_ptr<Request> upcast() const;
    std::unique_ptr<Request> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Request o);
class ZrestDB : public litesql::Database {
public:
    ZrestDB( const std::string& backendType, const std::string& connInfo);
protected:
    virtual std::vector<litesql::Database::SchemaItem> getSchema() const;
    static void initialize();
};
}
#endif
