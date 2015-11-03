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
    void compute_similarities();

private:
    // Unique terms encountered in the contents file
    set<string> unique_terms;
    set<string> unique_genres;
    set<string> unique_actors;
    set<string> unique_directors;
    set<string> unique_awards;

    // Inverse Document Frequency
    vector<float> genres_idf;

    // list of items and users with their positions in the utility matrix
    unordered_map<string, size_t> items;
    unordered_map<string, size_t> users;

    set<size_t> non_listed_items;
    set<size_t> non_listed_users;


    // target users to filter the vector sim computation
    set<size_t> target_users;

    // targets listed
    vector<vector<string> > targets;
    vector<pair<size_t, size_t>> targets_positions;


    // Item Contents information
    vector <ItemContent> item_contents;

    // The stats will hold the values for {count, avg, sum},
    vector<vector<float>> items_stats;
    vector<vector<float>> users_stats;

    // Storing the ratings with rows to build the utility matrix after
    vector<vector<string>> ratings_rows;

    // Utility matrix used to make faster the vote computation
    vector<vector<float>> utility_matrix;

    // Item Content Representations
    vector<vector<float>> items_genres_representation;
    vector<vector<float>> users_genres_representation;

    int total_items;

    vector<float> create_representation(set<string> &terms, vector<string> &hits, vector<float> &idf);


    void compute_similarities(vector<vector<float>> &items_representations,
                              vector<vector<float>> &users_representations);


    vector<vector<float>> compute_users_factors(vector<vector<float>> items_representations);
};


#endif //TP1_RECSYS_CONTENTRECOMMENDER_H
