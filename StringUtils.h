//
// Created by gorigan on 10/2/15.
//

#ifndef TP1_RECSYS_STRINGUTILS_H
#define TP1_RECSYS_STRINGUTILS_H

#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string &s, char delim);
std::vector<std::string> split(const std::string &str, const std::string &delimiter);
void remove_chars(std::string &s, std::string chars);
#endif //TP1_RECSYS_STRINGUTILS_H