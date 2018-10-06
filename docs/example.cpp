#include <iostream>
#include <string>
#include <stdexcept>
#include "database.h"
#include "dataresult.h"
#include "dataset.h"

DataResult selectAllCustomers();

int main(int argc, char** argv)
{
    DataResult result = selectAllCustomers();

    if (result.bad()) {
        std::cout << result.getError() << std::endl;
    }

    for(int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << std::endl;
    }

    return 0;
}

DataResult selectAllCustomers()
{
    const std::string sql = "SELECT * FROM CUSTOMER;";
    const std::string connection = "/var/lib/sqlite3/storeapp/store.db";

    Database db(connection);

    try {
        db.connect();
        db.select(sql);
        db.close();
        return db.getResult();
    }
    catch(const std::runtime_error& e) {
        db.close();
        return db.getResult();
    }
}
