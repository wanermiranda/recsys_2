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
    vector<string> Genres;
    vector<string> Directors;
    vector<string> Awards;
    vector<string> Actors;
    vector<string> PlotTerms;
    vector<string> Title;

    vector<string> content_values = split(json_contents, "\",\"");
    for (auto raw_token: content_values) {
        string token(raw_token);
        token = str2lower(token);
        token = remove_chars(token, "\"");
        string token_value = get_token_value(token);
        token = remove_chars(token, ",");
        if (token_value != NONE_STR) {
            if (!starts_with(token, "year") && !starts_with(token, "imdbrating"))
                token_value = remove_chars(token_value, INVALID_CHARS);

            if (starts_with(token, "title")) {
                Title = split(token_value, " ");
            }
            else if (starts_with(token, "genre"))
                Genres =  split(token_value, ",");

            /*else if (starts_with(token, "director")) {
                token_value = remove_chars(token_value," ");
                Directors = split(token_value, ",");
            }
            else if (starts_with(token, "actors")) {
                token_value = remove_chars(token_value, " ");
                Actors = split(token_value, ",");
            }*/

            else if (starts_with(token, "country"))
               MainTerms.push_back(token_value);

            else if (starts_with(token, "type")) {
               MainTerms.push_back(token_value);
            }
            
            else if (starts_with(token, "company"))
               MainTerms.push_back(token_value);

            else if (starts_with(token, "awards"))
                Awards = split(token_value, ",");

            else if (starts_with(token, "plot")) {
                token_value = remove_chars(token_value, ",");
                Plot = token_value;
            }
            // Extracting the decade 198X
            else if (starts_with(token, "year")) {
                    Year = stoi(token_value);
                    MainTerms.push_back(token_value.substr(0, token_value.size()-1) + "X");                 
            }
            else if (starts_with(token, "imdbrating")) {
                    imdbRating = stof(token_value);
            }
        }
    }

    
    append_vectors<string>(MainTerms, Title);

    for (size_t i = 0; i <= 5; i++)
        append_vectors<string>(MainTerms, Genres);    

    append_vectors<string>(MainTerms, Awards);


    /*Make the vector too much sparse */

    //append_vectors<string>(MainTerms, Actors);
    
    //append_vectors<string>(MainTerms, Directors);
    

    // Update main terms set to be used during the feature vector build
    for (string term: MainTerms)
        UniqueMainTerms.insert(term);


    // Make a reinforcement of the terms if they exists
    // in the plot too - The bool value stands for reinforcement only
    analyze_terms(PlotTerms, false);

    // Update main terms set to be used during the feature vector build
    append_vectors<string>(MainTerms, PlotTerms);

    for (string term: PlotTerms)
        UniqueMainTerms.insert(term);
    
    Title.clear();
    Genres.clear();
    Directors.clear();
    Actors.clear();
    PlotTerms.clear();
}

string ItemContent::get_token_value(const string &str) {
    string local_str(str);
    local_str = remove_chars(local_str, "\"");
    vector<string> key_value = split(local_str, ":");
    local_str = key_value[1];
    return local_str;
}

void ItemContent::analyze_terms(vector<string> &PlotTerms, bool reinforcement_only) {

    unordered_map<string, size_t> terms;
    string top_terms[N_TERMS];

    size_t top_terms_count[N_TERMS];
    // Initilizing
    for (int i = 0; i < N_TERMS; i++) {
        top_terms[i] = EMPTY_STR;
        top_terms_count[i] = SIZE_MAX;
    }

    // Loop through all words in the dictionary
    // Make a reinforcement of the terms if they exists
    // in the plot too
    vector<string> raw_terms = split(Plot, " ");
    for (string term: raw_terms) {
        term = str2lower(term);
        if ( STOP_WORDS.find(term) == STOP_WORDS.end() ) {
    	    if (UniqueMainTerms.find(term) != UniqueMainTerms.end())
                PlotTerms.push_back(term);

            else if (!reinforcement_only) {
                if (terms.find(term) == terms.end()) {
                    terms.insert({term, 1});
                }
                else
                    terms.at(term)++;          
            }  
        }
        
    }

    if (!reinforcement_only) {
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

        // Transferring the most common terms to the attributes
        for (int i = 0; i < N_TERMS; i++)
            if (top_terms[i] != EMPTY_STR){
    //            plot_pair_terms.push_back(make_pair(top_terms[i], top_terms_count[i]));
                PlotTerms.push_back(top_terms[i]);
                //DEBUG_ONLY(cout << i << "th pair: <" << top_terms[i] << ',' << top_terms_count[i] << '>' << endl);
            }
    }
    terms.clear();
    raw_terms.clear();

}

ItemContent::ItemContent() {

}

void ItemContent::clear_terms() {
    MainTerms.clear();
    UniqueMainTerms.clear();
}
