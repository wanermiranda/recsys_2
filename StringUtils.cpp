//
// Created by Waner Miranda on 10/2/15.
//

#include "StringUtils.h"
#include "Constants.h"
#include <algorithm>
#include <algorithm>
#include <sstream>
#include <iterator>
using namespace std;


string str2lower(string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

string remove_unwanted(const string s, char delim) {
    string elems;
    remove_unwanted(s, delim, elems);
    return elems;
}

string remove_unwanted(const string s, char delim, string &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        if (STOP_WORDS.find(item) == STOP_WORDS.end())
            elems += delim + item;
    }
    return elems;
}

//vector<string> split(const string s, char delim) {
//    vector<string> elems;
//    split(s, delim);
//    return elems;
//}

vector<string> split(const string str, const string delimiter) {
    std::vector<std::string> tokens;
    int start = 0, end = 0;
    while ((end = str.find(delimiter, start)) != std::string::npos) {
        string term =str.substr(start, end - start);
        if (STOP_WORDS.find(term) == STOP_WORDS.end())
            tokens.push_back(term);
        start = end + 1;
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

string remove_chars(string s, const string chars) {
    s.erase(remove_if(s.begin(), s.end(), [&chars](const char& c) {
        return chars.find(c) != string::npos;
    }), s.end());
    return s;

}

bool starts_with(const string str, const string prefix) {
    return (!str.compare(0, prefix.size(), prefix));
}
