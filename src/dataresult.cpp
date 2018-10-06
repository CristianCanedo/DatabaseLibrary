#include <string>
#include <memory>
#include "dataresult.h"
#include "dataset.h"

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

std::unique_ptr<DataResult> DataResult::ok(const DataSet& dataSet)
{
	return std::unique_ptr<DataResult>(new DataResult(dataSet));
}

std::unique_ptr<DataResult> DataResult::fail(std::string errmsg)
{
	return std::unique_ptr<DataResult>(new DataResult(errmsg));
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
    return !good();
}
