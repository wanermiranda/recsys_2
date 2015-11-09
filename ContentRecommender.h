//
// Created by Waner Miranda on 11/1/15.
//

#ifndef TP1_RECSYS_CONTENTRECOMMENDER_H
#define TP1_RECSYS_CONTENTRECOMMENDER_H
#include "Constants.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <array>
#include "ItemContent.h"

using namespace std;

class ContentRecommender {
public:
    void load_args(char **agv, int argc);
    void read_ratings(char *file_name);
    void read_contents(char *file_name);
    void read_targets(char *file_name);
    void build_utility_matrix();
    void build_representations();
    void compute_users_factors_matrix();

    void clear_representations();


    void do_content_predictions(vector<vector<float>> &items_representations, vector<vector<float>> &users_representations);

    void print_predictions();

    void do_content_predictions();

private:
    // Unique terms encountered in the contents file
    set<string> unique_main_terms;
    size_t unq_terms_sz;
    // Indexing the items by the each term
    unordered_map<size_t, set<size_t>> items_per_terms;
    //    set<string> unique_genres;
//    set<string> unique_actors;
//    set<string> unique_directors;
//    set<string> unique_awards;

    // Inverse Document Frequency
//    vector<float> genres_idf;
    vector<float> main_terms_idf;

    // list of items and users with their positions in the utility matrix
    unordered_map<string, size_t> items;
    unordered_map<string, size_t> users;

    set<size_t> non_listed_items;
    set<size_t> non_listed_users;


    // target users to filter the vector sim computation
    set<size_t> target_users;
    set<size_t> target_items;

    // targets listed
    vector<vector<string> > targets;
    vector<pair<size_t, size_t>> targets_positions;
    vector<float> targets_predictions;



    // Item Contents information
    vector<ItemContent> item_contents;

    // The stats will hold the values for {count, avg, sum},
    vector<vector<float>> items_stats;
    vector<vector<float>> users_stats;

    // Storing the ratings with rows to build the utility matrix after
    vector<tuple<size_t, size_t, float>> user_item_ratings;

    // Utility matrix used to make faster the vote computation
    vector<vector<float>> utility_matrix;

    // Item Content Representations
    vector<vector<float>> items_representation;
    size_t items_representations_size;
    vector<vector<float>> users_representation;
    size_t users_representations_size;


    int total_items;

    vector<float> create_representation(set<string> &terms, vector<string> &hits, vector<float> &idf);


    void compute_users_representations(vector<vector<float>> &items_representations, size_t term_count);

    size_t register_term_frequency(string term, set<string> &unique_values, vector<float> &values_idf, size_t item_pos);


};


#endif //TP1_RECSYS_CONTENTRECOMMENDER_H
