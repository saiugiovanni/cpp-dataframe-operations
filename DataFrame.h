#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <set>


#include "Column.h"


// additional types:
struct dimension {
    size_t rows;
    size_t cols;
};



// Helper functions:
void newLine(std::string s = "");


std::vector<std::string> addPrefix(const std::vector<std::string> & to, std::string prefix);



class DataFrame {
public:
    typedef std::string Key;
    typedef std::vector<Key> Keys;

    typedef std::map<Key, Column> dataFrameType;
    
    // let's use the inner components of std::map:
    typedef dataFrameType::value_type valueType;

    static std::string PREFIX1;
    static std::string PREFIX2;

private:
    dataFrameType dataFrameData;

    // return the names of columns in s separated by delim, as per "A B C"
    std::vector<std::string> split(const std::string &s, char delim) const;

    // returns true if columnName is valid (included in the constructor list)
    bool checkColumnName(const std::string &columnName) const;


public:
    explicit DataFrame(const std::string &columnNamesString);

    DataFrame() = default;

    Keys getColumnNames() const;

    Column getColumn(const Key &columnName) const;
     
    // set the values of an existing column
    void setColumn(const std::string &columnName,
                    const Column &column);

    // add a new column with data
    bool addColumn(const std::string &columnName,
                    const Column &column
                    );

    void print(void) const;
    dimension getDimension() const;


// TO BE IMPLEMENTED:
    DataFrame hstack(DataFrame &otherDataFrame);
    DataFrame join(DataFrame &otherDataFrame, std::string onMyCol, std::string onColOfOther);

    // ancillary code:
    DataFrame(std::vector<std::string> columnsNames);
    ValuesArray getValuesAtRow(size_t row)const;

};

#endif //DATAFRAME_H
