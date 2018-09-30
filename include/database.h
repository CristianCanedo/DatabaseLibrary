// database.h
#ifndef INCLUDED_DATABASE
#define INCLUDED_DATABASE

#include <string>
#include <vector>
#include "sqlite3.h"
#include "dataresult.h"

class Database {

typedef int (*callback_t)(void*, int, char**, char**);

private:
    sqlite3* d_database_p;
    DataResult* d_result_p;
    DataSet d_dataSet;
    std::string d_lastErrorMsg;

    static std::string s_dbPath;
    static bool s_seeded;

    callback_t callback;

    int executeSQL(std::string sql, char** errmsg);
    int generateUniqueId();
    static int selectCallback(void*, int argc, char** argv, char** colName);

public:
    // CREATORS
    Database();
    Database(std::string dbPath);
    ~Database();

    // MANIPULATORS
    Database& connect();
    Database& select(std::string sql);
    Database& insert(std::string sql);
    Database& update(std::string sql);
    void close();

    // ACCESSORS
    DataResult getResult() const;
};
#endif
