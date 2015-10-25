//
// Created by Waner Miranda on 10/2/15.
//

#ifndef TP1_RECSYS_CSVREADER_H
#define TP1_RECSYS_CSVREADER_H

#include "Constants.h"
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class CSVReader {
private:
    std::vector<std::string> _current_line;
    char _separator = ',';
public:
    CSVReader (char separator) {_separator=separator;}
    CSVReader () {}

    std::string const& operator[](std::size_t index) const
    {
        if (index > size()) {
            std::cout << "Index out of bounds." << std::endl;
            return NULL;
        }
        else return _current_line[index];


    }
    std::size_t size() const
    {
        return _current_line.size();
    }

    void read_line(std::ifstream&  str);

};

std::ifstream& operator>>(std::ifstream& str,CSVReader& data);
#endif //TP1_RECSYS_CSVREADER_H