#include <string>
#include <cstdlib>
#include <time.h>
#include <stdexcept>
#include <vector>
#include "../include/sqlite3.h"
#include "../include/database.h"
#include "../include/dataresult.h"
#include "../include/dataset.h"

bool Database::s_seeded = false;
std::string Database::s_dbPath = "/var/lib/sqlite3/storage/storage.db";

Database::Database()
{
    d_result_p = nullptr;

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
    d_result_p->release();
	delete d_result_p;
}

Database& Database::connect()
{
    if (sqlite3_open(s_dbPath.c_str(), &d_database_p) != SQLITE_OK) {
		sqlite3_close(d_database_p);
		throw std::runtime_error(sqlite3_errmsg(d_database_p));
    }
    return *this;
}

Database& Database::select(std::string sql)
{
    callback = selectCallback;
    char* errmsg;
    int rc = executeSQL(sql, &errmsg);

    if (rc != SQLITE_OK) {
		throw std::runtime_error(errmsg);
    }

	callback = nullptr;
    delete errmsg;
    return *this;
}

Database& Database::insert(std::string sql)
{
    callback = nullptr;
    char* errmsg;
    int rc = executeSQL(sql, &errmsg);
    
    if (rc != SQLITE_OK) {
		throw std::runtime_error(errmsg);
    }

    delete errmsg;
    return *this;
}

Database& Database::update(std::string sql)
{
	callback = nullptr;
    return *this;
}

void Database::close()
{
    if (sqlite3_close(d_database_p) != SQLITE_OK) {
		throw std::runtime_error(sqlite3_errmsg(d_database_p));
    }
}

DataResult Database::getResult() const
{
    return *d_result_p;
}

int Database::executeSQL(std::string sql, char** errorMsg)
{
    return sqlite3_exec(d_database_p, sql.c_str(), callback, &d_dataSet, errorMsg);
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
