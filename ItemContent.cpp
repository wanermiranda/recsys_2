//
// Created by Waner Miranda on 10/25/15.
//

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <unicode/ustream.h>
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

        if (starts_with(token, "Genre"))
            Genre = token_value;

        else if (starts_with(token, "Directors"))
            Directors = split(token_value, ',');

        else if (starts_with(token, "Awards"))
            Awards = split(token_value, ',');

        else if (starts_with(token, "Actors"))
            Actors = split(token_value, ',');

        else if (starts_with(token, "Plot"))
            Plot = token_value;

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

    analyze_terms();
    build_feature_vectors();
}

string ItemContent::get_token_value(const string &str) {
    string local_str(str);
    remove_chars(local_str, "\"");
    vector<string> key_value = split(local_str, ':');
    local_str = key_value[1];
    remove_chars(local_str, "\"");
    return local_str;
}

void ItemContent::print_debug(){
 DEBUG_ONLY( cout << "Genre: " << Genre << endl
                    << "Year: " << Year << endl
                    << "imdbRating: " << imdbRating << endl;
 );
    DEBUG_ONLY(cout  << "Directors: " << vector2String<string>(Directors) << endl
                       << "Awards: " << vector2String<string>(Awards) << endl
                       << "Actors: " << vector2String<string>(Actors) << endl);
}

void ItemContent::analyze_terms() {
    unordered_map<string, size_t> terms;
    string top_terms[N_TERMS];

    size_t top_terms_count[N_TERMS];
    // Initilizing
    for (int i = 0; i < N_TERMS; i++) {
        top_terms[i] = EMPTY_STR;
        top_terms_count[i] = SIZE_MAX;
    }
    // Loop through all words in the dictionary
    vector<string> raw_terms = split(Plot, ' ');
    for (string raw_term: raw_terms) {
        string term(raw_term);
        for_each(term.begin(), term.end(), convert2lower());
        remove_chars(term, "\',.:;()[]");
        if ((UNWANTED_TERMS.find(term) == UNWANTED_TERMS.end())
            && (term.length() > 3)) {
            if (terms.find(term) == terms.end()) {
                terms.insert({term, 1});
            }
            else
                terms.at(term)++;

        }
    }
    for (auto term_pair: terms) {
        // Looking for the N TERMS with most occurrences
        size_t hold_count = term_pair.second;
        string hold_term = term_pair.first;

        for (int i = 0; i < N_TERMS; i++) {
            if (hold_count < top_terms_count[i]) {
                // save actual value from the position
                size_t aux_count = top_terms_count[i];
                string aux_term = top_terms[i];

                //switch to the hold_values
                top_terms_count[i] = hold_count;
                top_terms[i] = hold_term;

                //hold the replaced values
                hold_count = aux_count;
                hold_term = aux_term;
            }
        }
    }
    // Transfering the most common terms to the attributes
    for (int i = 0; i < N_TERMS; i++)
        if (top_terms[i] != EMPTY_STR){
            NTerms.push_back( make_pair(top_terms[i], top_terms_count[i]));
//            DEBUG_ONLY(cout << i << "th pair: <" << top_terms[i] << ',' << top_terms_count[i] << '>' << endl);
        }

}

void ItemContent::build_feature_vectors() {
    int movie_decade = Year - 1930;

    movie_decade = (movie_decade < 0)?0:movie_decade;


    main_factors_vector.push_back(movie_decade);
}
