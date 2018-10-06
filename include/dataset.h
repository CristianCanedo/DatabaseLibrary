// dataset.h
#ifndef INCLUDED_DATASET
#define INCLUDED_DATASET

#include <string>
#include <vector>

struct Column {
private:
    std::string d_name;
    std::string d_value;

public:
    // CREATORS
    Column(std::string name, std::string value);

    // ACCESSORS
    std::string getName() const;
    std::string getValue() const;
};

struct Row {
private:
    std::vector<Column> d_column;

public:
    // CREATORS
    Row();

    // MANIPULATORS
    void addColumn(std::string name, std::string value);
    void addColumn(const Column& column);
    Row& operator+=(const Column& rhs);

    // ACCESSORS
    Column& operator[](int index);
};

struct DataSet {
private:
    std::vector<Row> d_rows;

public:
    // CREATORS
    DataSet();

    // MANIPULATORS
    void addRow(const Row& row);
    DataSet& operator+=(const Row& rhs);

    // ACCESSORS
    int size() const;
    Row& operator[](int index);
};
#endif
