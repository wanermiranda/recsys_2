//
// Created by Waner Miranda on 10/24/15.
//
#include <iostream>
#include <map>
#include <algorithm>
#include <unordered_map>
#include "ReadInputs.h"
#include "DebugUtils.h"
#include "ItemContent.h"

using namespace std;



int main(int argc, char **argv) {
    if (argc < 4) {
        cout << "usage: ./recommender content.csv ratings.csv targets.csv > output.csv";
        exit(1);
    }

    unordered_map<string, size_t> items;
    unordered_map<string, size_t> users;
    vector<size_t> target_users;
    vector<vector<string> > targets;

    // Item Contents information
    vector <ItemContent> item_contents;


    // The stats will hold the values for {count, avg, sum},
    vector<vector<float>> items_stats;
    vector<vector<float>> users_stats;

    vector<vector<string> > rows;

    read_ratings(argv[2], items, users, rows, items_stats, users_stats);

    read_targets(argv[3], items, users,
                 items_stats, users_stats,
                 targets, target_users);

    DEBUG_ONLY(cout << "Rows: " << rows.size() << endl
               << " Items: " << items.size() << endl
               << " Users: " << users.size() << endl
               << " Target pairs:" << targets.size() << endl
               << " Targets Users:" << target_users.size() << endl);

    read_contents(argv[1], items, item_contents);

}