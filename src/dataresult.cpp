#include <string>
#include "../include/dataresult.h"
#include "../include/dataset.h"

DataResult* DataResult::instance_p = nullptr;

DataResult::DataResult(const DataSet& dataSet)
    : d_dataSet(dataSet)
{
    success = true;
}

DataResult::DataResult(std::string errmsg)
    : d_errmsg(errmsg)
{
    success = false;
}

DataResult* DataResult::ok(const DataSet& dataSet)
{
    if (instance_p == nullptr) {
	instance_p = new DataResult(dataSet);
    }
    return instance_p;
}

DataResult* DataResult::fail(std::string errmsg)
{
    if (instance_p == nullptr) {
	instance_p = new DataResult(errmsg);
    }
    return instance_p;
}

Row& DataResult::operator[](int index)
{
    return d_dataSet[index];
}

bool DataResult::good() const
{
    return success;
}

bool DataResult::bad() const
{
    return success;
}
