#include <string>
#include <vector>
#include <algorithm>
#include "sqlquery.h"

SelectQuery::SelectQuery() {}

SelectQuery& SelectQuery::select()
{
    d_internal = "SELECT * ";
}

SelectQuery& SelectQuery::select(const std::vector<std::string>& columns)
{
    d_internal = "SELECT ";

    auto join = [d_internal](const std::string& col) { d_internal.append(col + ", "); };

    std::for_each(columns.begin(), columns.end(), join);

    // removes last comma and whitespace
    d_internal.erase(d_internal - 2);
    // return whitespace at end
    d_internal.push_back(" ");
}

SelectQuery& SelectQuery::from(std::string table)
{
    d_internal.append(table + " ");
}

SelectQuery& SelectQuery::where(std::string column, Condition con, std::string value)
{
    d_internal.append("WHERE " + column + " ");
    d_internal.append(getStringCondition(con) + " ");
    d_internal.append(value);
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

SelectQuery& SelectQuery::toString() const
{
    return (d_internal + ";");
}
