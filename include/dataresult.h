// dataresult.h
#ifndef INCLUDED_DATARESULT
#define INCLUDED_DATARESULT

#include <string>
#include <memory>
#include "dataset.h"

struct DataResult {
private:
    DataSet d_dataSet;
    std::string d_errmsg;

    bool success;

    // IMPLEMENTED, BUT PRIVATE
    DataResult(const DataSet& dataSet);
    DataResult(std::string errmsg);

public:
    // CREATORS
    static std::unique_ptr<DataResult> ok(const DataSet& dataSet);
    static std::unique_ptr<DataResult> fail(std::string errmsg);

    // ACCESSORS
    std::string getError() const;
    int size() const;
    Row& operator[](int index);

    bool good() const;
    bool bad() const;
};
#endif
