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
#define N_TERMS 10
#define INVALID_CHARS "\\/0123456789[]{}-\'.:;()[]"
//#define DEBUG

const std::string NONE_STR = "n/a";
const std::string EMPTY_STR = "";
const std::set<std::string>
        UNWANTED_TERMS = {"a", "an", "another", "any", "certain", "each", "every", "her", "his", "its", "its", "my",
                          "no", "our", "some", "that", "the", "their", "this", "and", "but", "or", "yet", "for", "nor",
                          "so", "as", "aboard", "about", "above", "across", "after", "against", "along", "around", "at",
                          "before", "behind", "below", "beneath", "beside", "between", "beyond", "but", "by", "down",
                          "during", "except", "following", "for", "from", "in", "inside", "into", "like", "minus",
                          "minus", "near", "next", "of", "off", "on", "onto", "onto", "opposite", "out", "outside",
                          "over", "past", "plus", "round", "since", "since", "than", "through", "to", "toward", "under",
                          "underneath", "unlike", "until", "up", "upon", "with", "without"};


#endif //RECSYS_2_CONSTANTS_H
