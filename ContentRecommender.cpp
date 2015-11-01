//
// Created by gorigan on 11/1/15.
//

#include "ContentRecommender.h"
#include "CSVReader.h"
#include "DebugUtils.h"
#include "StringUtils.h"
#include "RecommenderUtils.h"
#include "ArrayUtils.h"

void ContentRecommender::load_args(char **argv, int argc) {
    read_ratings(argv[2]);
    read_targets(argv[3]);
    read_contents(argv[1]);
}

void ContentRecommender::read_contents(char *filename) {
    DEBUG_ONLY(cout << "Reading contents..." << endl);
    CSVReader row_reader('{');
    ifstream contents_file(filename);
    // skipping header
    contents_file >> row_reader;
    unique_terms.clear();
    while (contents_file >> row_reader) {
        string item = row_reader[0];
        remove_chars(item, ",");
        size_t item_pos = items.at(item);
        string content = row_reader[1];
        remove_chars(content, "{}");
        ItemContent itemContent(content, item_pos,item);
        item_contents.push_back(itemContent);
        //itemContent.print_debug();

        // Update unique terms
        for (auto term_pair: itemContent.NTerms)
            unique_terms.insert(term_pair.first);
        // Update unique_genres
        for (auto genre: itemContent.Genres)
            unique_genres.insert(genre);
        // Update unique directors
        for (auto director: itemContent.Directors)
            unique_directors.insert(director);
        // Update unique actors
        for (auto actor: itemContent.Actors)
            unique_actors.insert(actor);
        // Update unique awards
        for (auto award: itemContent.Awards)
            unique_awards.insert(award);
    }
    DEBUG_ONLY(cout << "Unique terms: " << unique_terms.size() << endl
                    << "Genres: " << unique_genres.size() << endl
                    << "Actors: " << unique_actors.size() << endl
                    << "Directors: " << unique_directors.size() << endl
                    << "Awards: " << unique_awards.size() << endl);

}
void ContentRecommender::read_ratings(char *filename) {
    ifstream ratings_file(filename);
    CSVReader row_reader;
    size_t row_count = 0;
    // Skip the header
    DEBUG_ONLY(cout << "Reading ratings..." << endl);
    ratings_file >> row_reader;
    while (ratings_file >> row_reader) {
        vector<string> item_user = split(row_reader[0], ':');
        row_count++;
        ratings_rows.push_back(vector<string>({item_user[0], item_user[1], row_reader[1]}));
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
    DEBUG_ONLY(cout << "Rows: " << row_count << endl
               << " Items: " << items.size() << endl
               << " Users: " << users.size() << endl
    );
    DEBUG_ONLY(cout << "Computing average for items and users..." << endl);

    compute_stats_avg(items_stats);
    compute_stats_avg(users_stats);
}

void ContentRecommender::read_targets(char *filename) {
    CSVReader row_reader;
    unordered_map<string, size_t> located_users;
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

        if (located_users.find(targets[target_count][0]) == located_users.end()) {
            size_t user_pos = users.at(targets[target_count][0]);
            target_users.push_back(user_pos);
            located_users.insert({targets[target_count][0], user_pos});
        }


        target_count++;
    }

    DEBUG_ONLY(cout << "New Users: " << new_users << endl << "New Items: " << new_items << endl);
    DEBUG_ONLY(cout << " Target pairs:" << targets.size() << endl
                    << " Targets Users:" << target_users.size() << endl);
    targets_file.close();
}

void ContentRecommender::build_utility_matrix() {
    DEBUG_ONLY(cout << "Building Utility Matrix..." << endl);
    size_t row_count = users.size(), col_count = items.size();
    utility_matrix.resize(row_count, vector<float>(col_count));
    init_utility_matrix(items, users, utility_matrix);

    for (size_t index = 0; index < ratings_rows.size(); index++) {
        size_t user_pos = users.at(ratings_rows[index][0]);
        size_t item_pos = items.at(ratings_rows[index][1]);
        float vote = stod(ratings_rows[index][2]);

        utility_matrix[user_pos][item_pos] = vote;
    }
}