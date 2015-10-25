//
// Created by Waner Miranda on 10/25/15.
//

#include <iostream>
#include "ItemContent.h"
#include "StringUtils.h"
#include "DebugUtils.h"
#include "ArrayUtils.h"


ItemContent::ItemContent(string json_contents, size_t item_pos, string item_id) {
    ItemId = item_id;
    ItemPos = item_pos;

    vector<string> content_values = split(json_contents, "\",\"");
    for (auto token: content_values) {
        string token_value = get_token_value(token);
        remove_chars(token, "\"");
        if (starts_with(token, "Genre"))
            Genre = token_value;

        else if (starts_with(token, "Director"))
            Director = split(token_value, ',');

        else if (starts_with(token, "Awards"))
            Awards = split(token_value, ',');

        else if (starts_with(token, "Actors"))
            Actors = split(token_value, ',');

        else if (starts_with(token, "Year")) {
            if (token_value != NONE_STR)
                Year = stoi(token_value);
            else Year = 0;
        }
        else if (starts_with(token, "imdbRating")) {
            if (token_value != NONE_STR)
                imdbRating = stof(token_value);
            else imdbRating = FLOAT_NONE_VALUE;
        }
    }
}

string ItemContent::get_token_value(const string &str) {
    string local_str(str);
    remove_chars(local_str, "\"");
    vector<string> key_value = split(local_str, ':');
    return key_value[1];
}

void ItemContent::print_debug(){
 DEBUG_ONLY( cout << "Genre: " << Genre << endl
                    << "Year: " << Year << endl
                    << "imdbRating: " << imdbRating << endl;
 );
    DEBUG_ONLY(cout  << "Director: " << vector2String<string>(Director) << endl
                       << "Awards: " << vector2String<string>(Awards) << endl
                       << "Actors: " << vector2String<string>(Actors) << endl);
}