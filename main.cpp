//
// Created by Waner Miranda on 10/24/15.
//
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
#include "ReadInputs.h"
#include "DebugUtils.h"
#include "ItemContent.h"
#include "RecommenderUtils.h"

using namespace std;



int main(int argc, char **argv) {
    if (argc < 4) {
        cout << "usage: ./recommender content.csv ratings.csv targets.csv > output.csv";
        exit(1);
    }

    // list of items and users with their positions in the utility matrix
    unordered_map<string, size_t> items;
    unordered_map<string, size_t> users;

    // target users to filter the vector sim computation
    vector<size_t> target_users;
    // targets listed
    vector<vector<string> > targets;

    // Item Contents information
    vector <ItemContent> item_contents;

    // The stats will hold the values for {count, avg, sum},
    vector<vector<float>> items_stats;
    vector<vector<float>> users_stats;

    // Rows extracted from the ratings file
    vector<vector<string> > rating_rows;

    // Unique terms encountered in the conents file
    set<string> unique_terms;

    read_ratings(argv[2], items, users, rating_rows, items_stats, users_stats);

    read_targets(argv[3], items, users,
                 items_stats, users_stats,
                 targets, target_users);

    DEBUG_ONLY(cout << "Rows: " << rating_rows.size() << endl
               << " Items: " << items.size() << endl
               << " Users: " << users.size() << endl
               << " Target pairs:" << targets.size() << endl
               << " Targets Users:" << target_users.size() << endl);

    read_contents(argv[1], items, item_contents, unique_terms);
    DEBUG_ONLY(cout << "Unique terms: " << unique_terms.size() << endl);
    DEBUG_ONLY(cout << "Computing average for items and users..." << endl);

    compute_stats_avg(items_stats);
    compute_stats_avg(users_stats);

    DEBUG_ONLY(cout << "Building Utility Matrix..." << endl);

    build_utility_matrix(rating_rows, items, users);

}