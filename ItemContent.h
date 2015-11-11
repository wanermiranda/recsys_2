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
    ItemContent();

    // decided to have the public attributes
    // this will easy the access
    string ItemId; // String reference for the item id on the input file
    size_t ItemPos; // Position in the vectors and utility matrix

    // Bellow there is the selected metadata from the item
    float imdbRating;

    string Plot;
    size_t Year;


    vector<string> MainTerms;
    set<string> UniqueMainTerms;
//    set<size_t> MainTermsPositions;



    ItemContent(string json_contents, size_t item_pos, string item_id);

    string get_token_value(const string &str);


    void clear_terms();

private:
//    vector<pair<string, size_t>> plot_pair_terms;

    void analyze_terms(vector<string> &PlotTerms, bool reinforcement_only);
};


#endif //TP1_RECSYS_ITEMCONTENT_H
