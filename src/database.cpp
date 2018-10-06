#include <string>
#include <cstdlib>
#include <time.h>
#include <stdexcept>
#include <vector>
#include "sqlite3.h"
#include "database.h"
#include "dataresult.h"
#include "dataset.h"

bool Database::s_seeded = false;
std::string Database::s_dbPath = "";

Database::Database()
{
    d_result_p = nullptr;
	callback = NULL;

    if (!s_seeded) {
        srand(time(NULL));
        s_seeded = true;
    }
}

Database::Database(std::string dbPath)
{
    if (s_dbPath.empty()) {
        s_dbPath = dbPath;
    }
    Database();
}

Database::~Database()
{
	if (d_database_p != nullptr) {
        close();
	}
}

Database& Database::connect()
{
    if (sqlite3_open(s_dbPath.c_str(), &d_database_p) != SQLITE_OK) {
        std::string errmsg(sqlite3_errmsg(d_database_p));
        throw std::runtime_error("Database::connect(): " + errmsg);
    }

    return *this;
}

Database& Database::connect(std::string connectionString)
{
    s_dbPath = connectionString;
    connect();
    return *this;
}

Database& Database::select(std::string sql)
{
    callback = selectCallback;
    executeSQL(sql);

    d_result_p = DataResult::ok(d_dataSet);

    return *this;
}

Database& Database::insert(std::string sql)
{
    executeSQL(sql);
    return *this;
}

Database& Database::update(std::string sql)
{
    executeSQL(sql);
    return *this;
}

void Database::close()
{
    if (sqlite3_close(d_database_p) != SQLITE_OK) {
        std::string errmsg(sqlite3_errmsg(d_database_p));
        throw std::runtime_error("Database::close(): " + errmsg);
    }
}

std::string Database::getLastError() const
{
    return d_lastError;
}

DataResult Database::getResult() const
{
    return *d_result_p;
}

int Database::executeSQL(std::string sql)
{
    char* errmsg;
    int ret;
    
    ret = sqlite3_exec(d_database_p, sql.c_str(), callback, &d_dataSet, &errmsg);

    if (ret != SQLITE_OK) {
        std::string errMsg(errmsg);
        sqlite3_free(errmsg);
        delete errmsg;
        throw std::runtime_error("Database::executeSQL(): " + errMsg);
    }

    callback = NULL;
    delete errmsg;
	return ret;
}

int Database::generateUniqueId()
{
    const int min = 1;
    const int max = 5000;
    return rand() % max + min;
}

int Database::selectCallback(void* dataSet, int argc, char** argv, char** colName)
{
    struct DataSet *dset = (DataSet*)dataSet;
    Row row;
    std::string name, value;

    for(int i = 0; i < argc; ++i) {
        name = std::string(colName[i]);
        value = std::string(argv[i]);
        row.addColumn(name, value);
    }

    dset->addRow(row);
    return 0;
}
