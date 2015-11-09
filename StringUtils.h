//
// Created by Waner Miranda on 10/2/15.
//

#ifndef TP1_RECSYS_STRINGUTILS_H
#define TP1_RECSYS_STRINGUTILS_H

#include <string>
#include <sstream>
#include <vector>
using namespace std;
string remove_unwanted(const string s, char delim, string &elems);
string remove_unwanted(const string s, char delim);
string str2lower(string str);
std::string join(
        const std::vector<std::string> & tokens,
        const std::string & delimiter);
std::vector<std::string> split(
        const std::string & str,
        const std::vector<std::string> & delimiters);

vector<string> split(const string str, const string delimiter);
string remove_chars(string s, const string chars);
bool starts_with(const string str, const string prefix);
struct convert2lower {
    void operator()(char& c) { c = tolower((unsigned char)c); }

};

#endif //TP1_RECSYS_STRINGUTILS_H