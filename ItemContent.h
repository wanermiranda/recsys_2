//
// Created by Waner Miranda on 10/25/15.
//

#ifndef TP1_RECSYS_ITEMCONTENT_H
#define TP1_RECSYS_ITEMCONTENT_H
#include <string>
#include <stddef.h>
#include <vector>
#include "Constants.h"

using namespace std;

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

    ItemContent(string json_contents, size_t item_pos, string item_id);

    void print_debug();

    string get_token_value(const string &str);
};


#endif //TP1_RECSYS_ITEMCONTENT_H
