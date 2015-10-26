//
// Created by Waner Miranda on 10/24/15.
//
#include "DebugUtils.h"
#include "ReadInputs.h"
#include "CSVReader.h"
#include "StringUtils.h"
#include "ItemContent.h"
#include <sstream>
#include <fstream>
#include <string>


void read_contents(char *filename, unordered_map<string, size_t> &items, vector<ItemContent> &item_contents) {
    DEBUG_ONLY(cout << "Reading contents..." << endl);
    CSVReader row_reader('{');
    ifstream contents_file(filename);
    // skipping header
    contents_file >> row_reader;
    while (contents_file >> row_reader) {
        string item = row_reader[0];
        remove_chars(item, ",");
        size_t item_pos = items.at(item);
        string content = row_reader[1];
        remove_chars(content, "{}");
        ItemContent itemContent(content, item_pos,item);
//        itemContent.print_debug();
        item_contents.push_back(itemContent);

    }
}


void read_ratings(const char *filename, unordered_map<string, size_t> &items, unordered_map<string, size_t> &users,
                  vector<vector<string>> &rows, vector<vector<float>> &items_stats,
                  vector<vector<float>> &users_stats) {
    ifstream ratings_file(filename);
    CSVReader row_reader;
    size_t row_count = 0;
    // Skip the header
    DEBUG_ONLY(cout << "Reading ratings..." << endl);
    ratings_file >> row_reader;
    while (ratings_file >> row_reader) {
        vector<string> item_user = split(row_reader[0], ':');
        rows.push_back(vector<string>({item_user[0], item_user[1], row_reader[1]}));
        row_count++;

        float vote = stod(row_reader[1]);

        if (items.find(item_user[1]) != items.end()) {
            size_t item_pos = items.at(item_user[1]);
            items_stats[item_pos][0]++;

            if (items_stats[item_pos][2] == -1)
                items_stats[item_pos][2] = vote;
            else items_stats[item_pos][2] += vote;
        }
        else {
            items.insert({item_user[1], items.size()});
            items_stats.push_back(vector<float>({1, 0, vote}));
        }

        if ((users.find(item_user[0]) != users.end())) {
            size_t user_pos = users.at(item_user[0]);
            users_stats[user_pos][0]++;

            if (users_stats[user_pos][2] == -1)
                users_stats[user_pos][2] = vote;
            else users_stats[user_pos][2] += vote;

        } else {
            users.insert({item_user[0], users.size()});
            users_stats.push_back(vector<float>({1, 0, vote}));
        }
    }
    ratings_file.close();
}


void read_targets(char *filename, unordered_map<string, size_t> &items, unordered_map<string, size_t> &users,
                  vector<vector<float>> &items_stats, vector<vector<float>> &users_stats,
                  vector<vector<string>> &targets,
                  vector<size_t> &target_users) {
    CSVReader row_reader;
    DEBUG_ONLY(cout << "Reading targets..." << endl);
    ifstream targets_file(filename);
    size_t target_count = 0;
    size_t new_users = 0, new_items = 0;

    // Skip the header
    targets_file >> row_reader;
    while (targets_file >> row_reader) {

        targets.push_back(split(row_reader[0], ':'));

        if (items.find(targets[target_count][1]) == items.end()) {
            new_items ++;
            items_stats.push_back(vector<float>({0, 0, -1}));
            items.insert({targets[target_count][1], items.size()});
        }

        if (users.find(targets[target_count][0]) == users.end()) {
            new_users ++;
            users_stats.push_back(vector<float>({0, 0, -1}));
            users.insert({targets[target_count][0], users.size()});
        }


        target_count++;
    }

    DEBUG_ONLY(cout << "New Users: " << new_users << endl << "New Items: " << new_items << endl);

    targets_file.close();
}