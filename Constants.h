//
// Created by Waner Miranda on 10/24/15.
//
#include <string>
#include <vector>
#include <set>
#ifndef RECSYS_2_CONSTANTS_H
#define RECSYS_2_CONSTANTS_H
#define FLOAT_NONE_VALUE 0
#define VOTE_MAX_VALUE 10.0f
#define N_TERMS 7
#define NN 30
//#define DEBUG

const std::string NONE_STR = "N/A";
const std::string EMPTY_STR = "";
const std::set<std::string> UNWANTED_TERMS = {"this", "that","they", "from", "what", "with" };


#endif //RECSYS_2_CONSTANTS_H
