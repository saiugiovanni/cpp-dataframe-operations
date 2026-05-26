// DataFrame.cpp source file

#include <iomanip>
#include <algorithm>
#include "DataFrame.h"

std::string DataFrame::PREFIX1{"df1_"};
std::string DataFrame::PREFIX2{"df2_"};


// Helper functions Protos:
void tabbed(double value, bool showZeros = true);
void tabbed(std::string string);
void tab();
std::vector<std::string> addPrefix(const std::vector<std::string> & to, std::string prefix);




DataFrame::DataFrame(const std::string &columnNamesString) : DataFrame() {
    Keys columnsNames = split(columnNamesString, ' ');

    for (const Key &name: columnsNames)
        dataFrameData[name];
}


DataFrame::Keys DataFrame::split(const std::string &s, char delim) const {
    Key word;
    Keys v;
    std::istringstream columns(s);

    while (std::getline(columns, word, delim)) v.push_back(word);

    return v;
}

bool DataFrame::checkColumnName(const std::string &columnName) const {
    return dataFrameData.find(columnName) != dataFrameData.end();
}


Column DataFrame::getColumn(const std::string &columnName) const {
    if (checkColumnName(columnName))
        return dataFrameData.at(columnName);
    else {
        std::cerr << "Error, " << columnName << " is unknown" << std::endl;
        return Column();
    }
}


void DataFrame::setColumn(const std::string &columnName,
                           const Column &column) {
    if (checkColumnName(columnName))
        dataFrameData[columnName] = column;
    else
        std::cerr << "Error, " << columnName << " is unknown" << std::endl;
}



bool DataFrame::addColumn(const Key &columnName,
                           const Column &columnData) {
    if (!checkColumnName(columnName)) {
        dataFrameData[columnName] = columnData;
        return true;
    }
    else {
        return false;
    }
}



std::vector<DataFrame::Key> DataFrame::getColumnNames() const {

    Keys names = Keys();

    for (const valueType &element: dataFrameData) {
        std::string s = element.first;
        names.push_back(s);
    }

    return names;
}


// // we se are simulating arrays, number or rows will be the max value in keys
dimension DataFrame::getDimension() const {
    auto colNames = getColumnNames();
    if (colNames.empty()){
        return {0,0};
    }

    auto cols = colNames.size();

    // cannot be equal, se we have sparse columns:

    /* if dense, every column with same height, so:
    auto values0 = get_column(colNames[0]);
    auto rows = values0.height();
     */
    
    // but we must search for max key:
    size_t rows = 0;
    for(std::string name: colNames){
        auto values = getColumn(name);
        auto H = values.height();
        rows = std::max(rows, H);
    }
    
    return {rows, cols};
}



void DataFrame::print(void) const {

    // write all columns names:
    auto colNames = getColumnNames();
    for (auto t: colNames) {
        tabbed(t);
    }

    newLine();

    auto dimension = getDimension();
    
    if (dimension.rows == 0)
        return;

    for (int row = 0; row < dimension.rows; row++) {

        auto valuesArray = getValuesAtRow(row);
            for(auto v : valuesArray){
                tabbed(v);
            }
            newLine();
    }

    newLine();
}


// TO BE IMPLEMENTED:

DataFrame
DataFrame::hstack(DataFrame &otherDataFrame){
    // YOUR CODE HERE
    // only to allow RUN: (please write your own code)

    // If both the dataframe have dimension zero I return an empty dataframe
    if(otherDataFrame.getDimension().rows ==0 && otherDataFrame.getDimension().cols ==0 &&
        getDimension().rows ==0 && getDimension().cols ==0)
        return DataFrame{};

    Keys prefix_1 = addPrefix(getColumnNames(),PREFIX1); // I store the prefix of the column names of the first dataframe
    DataFrame hstack_dataFrame(prefix_1); //I initialise my dataframe hstack_dataFrame adding the names of the first dataframe
    // Now I copy the first dataframe into the new dataframe hstack_dataFrame.
    // If the first dataframe is empty I store only the column indexes --> prefix_1
    auto column_names = getColumnNames();
    auto it1 = prefix_1.cbegin();
    for (const auto & name_column : column_names) // I loop over all the columns by their names
        hstack_dataFrame.setColumn(*it1++, getColumn(name_column)); // I exploit the setcolumn which add the column returned by the getColumn function in the position relative to the iterator it1

    // Now I add the second dataframe "otherDataFrame" into hstack_dataFrame
    // If the second dataframe is empty I store only the column indexes --> prefix_2
    Keys prefix_2 = addPrefix(otherDataFrame.getColumnNames(),PREFIX2); // I store the prefix of the column names of the second dataframe
    size_t k2 = 0;
    auto it2 = otherDataFrame.dataFrameData.cbegin();
    while(it2 != otherDataFrame.dataFrameData.cend()){ // I loop over the second dataframe
        Column cdata2 = it2++->second ;  // I store at each  step the column I want to add
        hstack_dataFrame.dataFrameData.insert({prefix_2[k2++],cdata2}); // I use the command insert to add the column to the dataframe hstack_dataFrame
    }

    return hstack_dataFrame;
}

DataFrame DataFrame::join(DataFrame &otherDataFrame, std::string onMyCol, std::string onColOfOther){
    // YOUR CODE HERE
    // only to allow RUN: (please write your own code)

    // If at least one of the 2 dataframes are empty ( dimension equals to 0 ) I return an empty dataframe because obviously there is no equality
    if (otherDataFrame.getDimension().rows == 0 && otherDataFrame.getDimension().cols == 0 ||
        getDimension().rows == 0 && getDimension().cols == 0)
        return DataFrame{};

    Keys prefix_1 = addPrefix(getColumnNames(), PREFIX1); // I store the prefix of the column names of the first dataframe
    DataFrame joint_dataframe(prefix_1); // I initialise the joint dataframe with name of the columns
    Keys prefix_2 = addPrefix(otherDataFrame.getColumnNames(), PREFIX2); // I store the prefix of the column names of the second dataframe
    for(auto key_col : prefix_2)
        joint_dataframe.dataFrameData[key_col]; // I add the second prefixes after the first ones

    Column mycol_data = getColumn(onMyCol); // I store the column onMyCol in input
    Column othercol_data = otherDataFrame.getColumn(onColOfOther); // I store the column onColOfOther in input

    // I create a new map to store the indexes of the columns taken into consideration.
    // acces key,  indexes of mycol, indexes of othercol
    std::map<size_t, std::pair<size_t, size_t> > map_ind_mc_oc;
    size_t m = 0;
    for (auto it_mycol = mycol_data.values.cbegin(); it_mycol != mycol_data.values.cend(); it_mycol++) { // I loop over the element of the column mycol_data
        for (auto it_oth = othercol_data.values.cbegin(); it_oth != othercol_data.values.cend(); it_oth++) { // I loop over the element of the column othercol_data
            if (it_mycol->second == it_oth->second) { // When the values are equals I enter in this if condition which will store the index of the columns in the map created above
                auto it_m_index = it_mycol->first;
                auto it_o_index = it_oth->first;
                map_ind_mc_oc[m++] = {it_m_index, it_o_index};
            }
        }
    }

    // I loop all over the map of indexes that I just created and filled.
    for (auto map_it = map_ind_mc_oc.cbegin(); map_it != map_ind_mc_oc.cend(); map_it++) {
        ValuesArray row_val_df1 = getValuesAtRow(map_it->second.first); // I store the values of the row of the first dataframe which has the element on the column ON_MY_COL equals to a value in ON_OTHER_COLUMN
        ValuesArray row_val_df2 = otherDataFrame.getValuesAtRow(map_it->second.second); // Same as above but I take the row from the second dataframe
        size_t row1 = 0; // Index to pass row_val_df1
        size_t row2 = 0; // Index to pass row_val_df2
        auto j = joint_dataframe.dataFrameData.cbegin();
        while( j != joint_dataframe.dataFrameData.cend() ){ // Now I do a loop all over the dataFrameData I want to return
            if (row1 < row_val_df1.size()) { // I access the element of the row of the first dataframe
                if (row_val_df1[row1] != 0) { // I store the values only if it is different than 0
                    joint_dataframe.dataFrameData[j->first].insert(row_val_df1[row1],map_it->first); // I use the c-lion command.insert( value:, atRow:)
                }
                row1++; // I increase the index of row_val_df1 even if I did not add anything ( case when the value is 0 )
            }
            else if (row2 < row_val_df2.size()) { // Now I add the values of row of the second dataframe --> same steps
                if (row_val_df2[row2] != 0) {
                    joint_dataframe.dataFrameData[j->first].insert(row_val_df2[row2], map_it->first);
                }
                row2++;
            }
            j++;
        }
    }

    return joint_dataframe;
}


// ancillary code

DataFrame::DataFrame(std::vector<std::string> columnsNames)
: DataFrame() {
    for (const Key &name: columnsNames)
        dataFrameData[name];
}


ValuesArray DataFrame::getValuesAtRow(size_t row) const{
    ValuesArray result = {};
    
    auto colNames = getColumnNames();
    for (auto name:colNames) {
        auto column = getColumn(name);
        auto value = column.values[row];
        result.push_back(value);
    }
    return result;
}




// MARK: Helper functions:



void tabbed(double value, bool showZeros){

    if (value == 0 && !showZeros){
        std::cout << "       " << "|";
    }else{
        std::cout << std::setw(7);
        std::cout << value << "|";
    }
}



void tabbed(std::string string){
    auto stdLen = 7;
    auto len = string.size();
    auto spaces = stdLen-len;
    std::cout << string;
    for (int i = 0; i < spaces; ++i) {
        std::cout << " ";
    }
    std::cout << "|";

}

void tab(){
    tabbed("");
}

void newLine(std::string s){
    std::cout << s << std::endl;
}



std::vector<std::string> addPrefix(const std::vector<std::string> & to, std::string prefix){
    std::vector<std::string> out;

    std::transform(to.begin(), to.end(),
                   std::back_inserter(out),
                   [&prefix](std::string v) { return prefix+v; }
    );
    return out;
}

