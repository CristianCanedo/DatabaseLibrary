#include <string>
#include "catch.hpp"
#include "database.h"

class DatabaseTestFixture {
protected:
    Database db;

public:
    DatabaseTestFixture() {}
};

TEST_CASE_METHOD(DatabaseTestFixture, "Establish Connection/Empty", "[database]")
{
    REQUIRE_THROWS(db.connect(""));
}
