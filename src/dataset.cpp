#include <string>
#include "../include/dataset.h"

Column::Column(std::string name, std::string value)
    : d_name(name), d_value(value) {}

std::string Column::getName() const
{
    return d_name;
}

std::string Column::getValue() const
{
    return d_value;
}

Row::Row() {}

void Row::addColumn(std::string name, std::string value)
{
    d_column.push_back(Column(name, value));
}

void Row::addColumn(const Column& column)
{
    d_column.push_back(column);
}

Row& Row::operator+=(const Column& rhs)
{
    d_column.push_back(rhs);
    return *this;
}

Column& Row::operator[](int index)
{
    return d_column[index];
}

DataSet::DataSet() {}

void DataSet::addRow(const Row& row)
{
    d_rows.push_back(row);
}

DataSet& DataSet::operator+=(const Row& rhs)
{
    d_rows.push_back(rhs);
    return *this;
}

Row& DataSet::operator[](int index)
{
    return d_rows[index];
}
