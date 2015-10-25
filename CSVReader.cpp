#include "CSVReader.h"


void CSVReader::read_line(std::ifstream& str) {
    std::string line;
    std::getline(str, line);

    std::stringstream line_stream(line);
    std::string cell;

    _current_line.clear();
    while (std::getline(line_stream, cell, _separator)) {
        _current_line.push_back(cell);
    }
}

std::ifstream& operator>>(std::ifstream& str,CSVReader& data)
{
    data.read_line(str);
    return str;
}