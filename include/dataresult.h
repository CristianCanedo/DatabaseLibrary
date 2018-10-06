// dataresult.h
#ifndef INCLUDED_DATARESULT
#define INCLUDED_DATARESULT

#include <string>
#include "dataset.h"

struct DataResult {
private:
    static DataResult* s_instance_p;
	static int d_count;
    DataSet d_dataSet;
    std::string d_errmsg;

    bool success;

    // IMPLEMENTED, BUT PRIVATE
    DataResult(const DataSet& dataSet);
    DataResult(std::string errmsg);
	~DataResult();

	void addRefToCount();
	void removeRefFromCount();

public:
    // CREATORS
    static DataResult* ok(const DataSet& dataSet);
    static DataResult* fail(std::string errmsg);
	static void release();

    // ACCESSORS
    Row& operator[](int index);

    bool good() const;
    bool bad() const;
};
#endif
