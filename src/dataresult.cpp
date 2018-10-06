#include <string>
#include "../include/dataresult.h"
#include "../include/dataset.h"

DataResult* DataResult::s_instance_p = nullptr;
int DataResult::d_count = 0;

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

DataResult::~DataResult() {}

DataResult* DataResult::ok(const DataSet& dataSet)
{
    if (s_instance_p == nullptr) {
	s_instance_p = new DataResult(dataSet);
    }

	addRefToCount();
    return s_instance_p;
}

DataResult* DataResult::fail(std::string errmsg)
{
    if (s_instance_p == nullptr) {
	s_instance_p = new DataResult(errmsg);
    }

	removeRefFromCount();
    return s_instance_p;
}

void DataResult::release()
{
	removeRefFromCount();

	if (d_count == 0 && s_instance_p != nullptr) {
		delete s_instance_p;
		s_instance_p = nullptr;
	}
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

void DataResult::addRefToCount()
{
	++d_count;
}

void DataResult::removeRefFromCount()
{
	--d_count;
}
