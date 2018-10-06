#include <string>
#include "catch.hpp"
#include "database.h"

class DatabaseTestFixture {
private:
    Database db;

public:
    DatabaseTestFixture() {}
};

TEST_CASE_METHOD(DatabaseTestFixture, "Establish Connection/Empty", "[database]")
{
    REQUIRE_THROWS(db.connect(""));
}
