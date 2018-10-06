// database.h
#ifndef INCLUDED_DATABASE
#define INCLUDED_DATABASE

#include <memory>
#include <string>
#include <vector>
#include "sqlite3.h"
#include "dataresult.h"

class Database {

typedef int (*callback_t)(void*, int, char**, char**);

private:
    sqlite3* d_database_p;
    std::unique_ptr<DataResult> d_result_p;
    DataSet d_dataSet;
    callback_t d_callback;
    std::string d_lastError;

    static std::string s_dbPath;
    static bool s_seeded;

    int executeSQL(std::string sql);
    int generateUniqueId();
    static int selectCallback(void*, int argc, char** argv, char** colName);

public:
    // CREATORS
    Database();
    Database(std::string dbPath);
    ~Database();

    // MANIPULATORS
    Database& connect();
    Database& connect(std::string connectionString);
    Database& select(std::string sql);
    Database& insert(std::string sql);
    Database& update(std::string sql);
    void setcallback(callback_t);
    void close();

    // ACCESSORS
    std::string getLastError() const;
    DataResult getResult() const;
};
#endif
