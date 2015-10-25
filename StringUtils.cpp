//
// Created by gorigan on 10/2/15.
//

#include "StringUtils.h"
#include <algorithm>
using namespace std;

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

vector<string> split(const string &str, const string &delimiter) {
    size_t pos = 0;
    string token;
    vector<string> output;
    string s = str;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        output.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    return output;
}

void remove_chars(string &s, string chars) {
    s.erase(remove_if(s.begin(), s.end(), [&chars](const char& c) {
        return chars.find(c) != string::npos;
    }), s.end());

}