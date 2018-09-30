// dataresult.h
#ifndef INCLUDED_DATARESULT
#define INCLUDED_DATARESULT

#include <string>
#include "dataset.h"

struct DataResult {
private:
    static DataResult* instance_p;
    DataSet d_dataSet;
    std::string d_errmsg;

    bool success;

    // IMPLEMENTED, BUT PRIVATE
    DataResult(const DataSet& dataSet);
    DataResult(std::string errmsg);

public:
    // CREATORS
    static DataResult* ok(const DataSet& dataSet);
    static DataResult* fail(std::string errmsg);

    // ACCESSORS
    Row& operator[](int index);

    bool good() const;
    bool bad() const;
};
#endif
