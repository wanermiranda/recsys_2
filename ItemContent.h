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
    string ItemId; // String reference for the item id on the input file
    size_t ItemPos; // Position in the vectors and utility matrix

    // Bellow there is the selected metadata from the item
    string Genre;
    float imdbRating;
    vector<string> Director;
    vector<string> Awards;
    vector<string> Actors;
    string Plot;
    size_t Year;

    ItemContent(string json_contents, size_t item_pos, string item_id);

    void print_debug();

    string get_token_value(const string &str);

    void analyze_terms();

    pair<string, size_t> NTerms[N_TERMS];
};


#endif //TP1_RECSYS_ITEMCONTENT_H
