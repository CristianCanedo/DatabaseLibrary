#include <string>
#include <vector>
#include <algorithm>
#include "sqlquery.h"

SelectQuery::SelectQuery() {}

SelectQuery& SelectQuery::select()
{
    d_internal = "SELECT * ";
    return *this;
}

SelectQuery& SelectQuery::select(const std::vector<std::string>& columns)
{
    d_internal = "SELECT ";

    auto join = [this](const std::string& col) { this->d_internal.append(col + ", "); };

    std::for_each(columns.begin(), columns.end(), join);

    // removes last comma and whitespace
    d_internal.erase(d_internal.length() - 2);
    // return whitespace at end
    d_internal.push_back(' ');
    return *this;
}

SelectQuery& SelectQuery::from(std::string table)
{
    d_internal.append(table + " ");
    return *this;
}

SelectQuery& SelectQuery::where(std::string column, Condition con, std::string value)
{
    d_internal.append("WHERE " + column + " ");
    d_internal.append(getStringCondition(con) + " ");
    d_internal.append(value);
    return *this;
}

std::string SelectQuery::getStringCondition(Condition con)
{
    switch(con) {
        case Condition::EQUALS:
            return "=";
        case Condition::GREATER_THAN:
            return ">";
        case Condition::GREATER_EQUAL:
            return ">=";
        case Condition::LESS_THAN:
            return "<";
        case Condition::LESS_EQUAL:
            return "<=";
        default:
            return "";
    }
}

std::string SelectQuery::toString() const
{
    return (d_internal + ";");
}
