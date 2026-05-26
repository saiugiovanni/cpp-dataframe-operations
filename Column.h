//
// Created by ing.conti on 22/11/22.
//

#ifndef DATAFRAME_COLUMN_H
#define DATAFRAME_COLUMN_H

#include <vector>
#include <map>
#include <cmath>
#include <string>




typedef double Value;
typedef std::vector<Value> ValuesArray;
typedef std::map<size_t, Value> Values;

class Column {
public:

    Values values;

    Column() {
    }

    Column(const Values &values) : values(values) {}

    // sparse constructor from string:
    Column(const std::string &stringOfValues);
    
    size_t height() const;
    void insert(const Value value, const size_t atRow);
    void print(std::string name) const;
    
};


#endif //DATAFRAME_COLUMN_H
