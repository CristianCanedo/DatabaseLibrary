// sqlquery.h
#ifndef INCLUDED_SQLQUERY
#define INCLUDED_SQLQUERY

#include <string>
#include <vector>

enum class Condition {
    EQUALS,
    GREATER_THAN,
    GREATER_EQUAL,
    LESS_THAN,
    LESS_EQUAL
};

struct SelectQuery {
private:
    std::string d_internal;

    std::string getStringCondition(Condition con);

public:
    // CREATORS
    SelectQuery();

    // MANIPULATORS
    SelectQuery& select();
    SelectQuery& select(const std::vector<std::string>& columns);
    SelectQuery& from(std::string table);
    SelectQuery& where(std::string column, Condition con, std::string value);

    // ACCESSORS
    std::string toString() const;
};

#endif
