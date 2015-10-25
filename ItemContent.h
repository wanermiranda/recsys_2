//
// Created by gorigan on 10/25/15.
//

#ifndef TP1_RECSYS_ITEMCONTENT_H
#define TP1_RECSYS_ITEMCONTENT_H
#include <string>
#include <stddef.h>

class ItemContent {
public:
    // decided to have the public attributes
    // this will easy the access
    string ItemId;
    size_t ItemPos;
    string Genre;
    float imdbRating;
    vector<string> Director;
    vector<string> Awards;
    vector<string> Actors;
    size_t Year;
};


#endif //TP1_RECSYS_ITEMCONTENT_H
