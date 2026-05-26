//
// Created by ing.conti on 22/11/22.
//


#include "Column.h"

#include <string>
#include <iostream>
#include <sstream>
#include<algorithm>


std::string trim(std::string str){
    str.erase(remove(str.begin(),str.end(),' '),str.end());
    return str;
}

// sparse constructor from string:
Column::Column(const std::string &stringOfValues){
    
    auto delim = ',';
    std::istringstream ss(trim(stringOfValues));
    
    size_t row = 0;
    for (std::string asciiValue; std::getline(ss, asciiValue, delim) ; ){
        
        Value v;
        if (asciiValue.length()>0){
            v = std::stod(asciiValue);
            insert(v, row);
        }
        row++;
    }
}

size_t Column::height() const{
        
    if (values.empty()) {
        return 0;
    }
    
    size_t maxKey = 0; // we use keys to simulate rows in array.
    maxKey = std::prev(values.end())->first;
    return maxKey+1;
}

void Column::insert(const Value value, const size_t atRow){
    values[atRow] = value;
}


void Column::print(std::string name)const{

    std::cout << std::endl  << "COL: " << name  << std::endl;
    
    for(auto it=values.begin();it !=values.end();++it) {
        //std::cout << "Key: " << it->first << " Value: " << it->second << "| " ;
        std::cout << "[" << it->first << "] = " << it->second << std::endl;
       }

}



