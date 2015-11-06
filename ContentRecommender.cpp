//
// Created by Waner Miranda on 11/1/15.
//

#include "ContentRecommender.h"
#include "CSVReader.h"
#include "DebugUtils.h"
#include "StringUtils.h"
#include "RecommenderUtils.h"
#include "ArrayUtils.h"
#include "distances.h"
#include <stddef.h>
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
    total_items = 0;
    item_contents.resize(items.size());
    while (contents_file >> row_reader) {
        total_items ++;
        string item = row_reader[0];
        remove_chars(item, ",");
        size_t item_pos = items.at(item);
        if (target_items.find(item_pos) != target_items.end()) {
            string content = row_reader[1];
            remove_chars(content, "{}");
            ItemContent itemContent(content, item_pos, item);
            item_contents[item_pos] = itemContent;
            //itemContent.print_debug();

            // Update unique terms
            for (auto term: itemContent.MainTerms) {
                register_term_frequency(term, unique_main_terms, main_terms_idf);
            }

            DEBUG_ONLY(cout << "Items read: " << total_items << endl);
        }
    }

    for (int idx =0; idx < main_terms_idf.size(); idx ++)
        main_terms_idf[idx] = log(total_items / main_terms_idf[idx]);

    DEBUG_ONLY(cout << "Unique terms: " << unique_terms.size() << endl
                    << "Genres: " << unique_genres.size() << endl
                    << "Genres IDF Count: " << main_terms_idf.size() << endl
                    << "Actors: " << unique_actors.size() << endl
                    << "Directors: " << unique_directors.size() << endl
                    << "Awards: " << unique_awards.size() << endl);

}

void ContentRecommender::register_term_frequency(const string &value, set<string> &unique_values,
                                                 vector<float> &values_idf) const {
    unique_values.insert(value);
    size_t value_pos = distance(unique_values.begin(), unique_values.find(value));
    if (unique_values.size() > values_idf.size())
                values_idf.push_back(1);
            else values_idf[value_pos] ++;
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

    DEBUG_ONLY(cout << "Reading targets..." << endl);
    ifstream targets_file(filename);
    size_t target_count = 0;
    size_t new_users = 0, new_items = 0;

    // Skip the header
    targets_file >> row_reader;
    while (targets_file >> row_reader) {
        size_t user_pos = 0, item_pos = 0;
        targets.push_back(split(row_reader[0], ':'));
        string user_id = targets[target_count][0];
        string item_id = targets[target_count][1];
        if (items.find(item_id) == items.end()) {
            new_items ++;
            items_stats.push_back(vector<float>({0, 0, -1}));
            item_pos = items.size();
            items.insert({item_id, item_pos});
            non_listed_items.insert(item_pos);
        } else item_pos = items.at(item_id);

        if (users.find(user_id) == users.end()) {
            new_users ++;
            users_stats.push_back(vector<float>({0, 0, -1}));
            user_pos = users.size();
            users.insert({user_id, user_pos});
            non_listed_users.insert(user_pos);
        } else user_pos = users.at(user_id);


        target_users.insert(user_pos);
        target_items.insert(item_pos);
        targets_positions.push_back({user_pos,item_pos});

        target_count++;
    }

    DEBUG_ONLY(cout << "New Users: " << new_users << " "  << non_listed_users.size() << endl
               << "New Items: " << new_items << " " << non_listed_items.size() << endl);
    DEBUG_ONLY(cout << " Target pairs:" << targets_positions.size() << endl
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

vector<float> ContentRecommender::create_representation(set<string> &terms, vector<string> &hits, vector<float> &idf) {
    vector<float> representation(terms.size());
    for (auto hit : hits) {
        if (terms.find(hit) != terms.end()) {
            size_t term_pos = distance(terms.begin(), terms.find(hit));
            representation[term_pos] = 1 * idf[term_pos];
        }
    }
//    DEBUG_ONLY(cout << "Representation: " << vector2String<float>(representation) << endl);
    return representation;
}

void ContentRecommender::build_representations() {
    int item_content_pos = 0;
    items_representation.resize(item_contents.size(), vector<float>(unique_main_terms.size()));
    for (auto item_content : item_contents) {
        items_representation[item_content_pos] = create_representation(unique_main_terms, item_content.MainTerms, main_terms_idf);
        item_content_pos++;
    }

}

void ContentRecommender::compute_similarities(vector<vector<float>> &items_representations,
                                              vector<vector<float>> &users_representations) {
    // Calculating vectors norms to improve performance
    vector<float> items_vectors_norms(items_representations.size());
    vector<float> users_vectors_norms(users_representations.size());

    for (int idx = 0; idx < items_representations.size(); idx++) {
        items_vectors_norms[idx] = vector_norm(items_representations[idx]);
    }

    for (int idx = 0; idx < users_representations.size(); idx++) {
        users_vectors_norms[idx] = vector_norm(users_representations[idx]);
    }

    similar_items_NN.resize(items_representations.size(), vector<pair<size_t, float>>(NN));

    // Looping through the user representations to get its similar items
    for (int idx_query = 0; idx_query < users_representations.size(); idx_query++) {
        for (int nn_pos = 0; nn_pos < NN; nn_pos++) {
            similar_items_NN[idx_query][nn_pos] = {0, 0};
        }
        // Comparing user x items
        for (int idx_target = 0; idx_target < items_representations.size(); idx_target++) {
            // ignore if there is a Null vector in the pair query x target
            if (users_vectors_norms[idx_query] * items_vectors_norms[idx_target] > 0) {
                float cosine = 0;
                cosine = dot_product(users_representations[idx_query], items_representations[idx_target]) /
                         (users_vectors_norms[idx_query] * items_vectors_norms[idx_target]);

                float hold_cosine = cosine;
                size_t hold_position = idx_target;

                for (int nn_pos = 0; nn_pos < NN; nn_pos++)
                    if (similar_items_NN[idx_query][nn_pos].second < hold_cosine) {
                        swap(hold_position, similar_items_NN[idx_query][nn_pos].first);
                        swap(hold_cosine, similar_items_NN[idx_query][nn_pos].second);
                    }
            }
        }
        DEBUG_ONLY(cout << idx_query << "/" << users_representations.size() << endl);
//        DEBUG_ONLY(cout << vectorPairs2String<size_t, float>(similar_items_NN[idx_query]) << endl;)
    }
}

void ContentRecommender::do_content_predictions(vector<vector<float>> &items_representations,
                                                vector<vector<float>> &users_representations) {
    size_t missing = 0;
    // Calculating vectors norms to improve performance
    vector<float> items_vectors_norms(items_representations.size());
    vector<float> users_vectors_norms(users_representations.size());

    targets_predictions.resize(targets_positions.size());

    for (int idx = 0; idx < items_representations.size(); idx++) {
        items_vectors_norms[idx] = vector_norm(items_representations[idx]);
    }

    for (int idx = 0; idx < users_representations.size(); idx++) {
        users_vectors_norms[idx] = vector_norm(users_representations[idx]);
    }

    // Comparing user x items
    for (int idx_target = 0; idx_target < targets_positions.size(); idx_target++) {
        size_t user_pos = targets_positions[idx_target].first;
        // Since the representation was created only for the target users we need to locate it into the set
        size_t target_user_pos = distance(target_users.find(user_pos), target_users.end());
        size_t item_pos = targets_positions[idx_target].second;
        // ignore if there is a Null vector in the pair query x target
        if (users_vectors_norms[target_user_pos] * items_vectors_norms[item_pos] > 0) {
            float cosine = dot_product(users_representations[target_user_pos], items_representations[item_pos]) /
                           (users_vectors_norms[target_user_pos] * items_vectors_norms[item_pos]);
            targets_predictions[idx_target] = cosine * VOTE_MAX_VALUE;
        }
        else  {
            targets_predictions[idx_target] = item_contents[item_pos].imdbRating;
            missing ++;
        }

        DEBUG_ONLY(cout << idx_target << "/" << targets_positions.size() << endl);
    }

    DEBUG_ONLY(cout << "Missing : " << missing << endl;)
}

vector<vector<float>> ContentRecommender::compute_users_factors(vector<vector<float>> items_representations) {
    size_t term_count = items_representations[0].size();
    vector<vector<float>> users_representations(target_users.size(), vector<float>(term_count));
    // Create a representation considering terms by user
    size_t missing_terms_user = 0;
    // Iterating users in the target list
    size_t user_idx = 0;
    for (auto user_pos : target_users) {
        float item_count = 0;
        size_t zero_count = 0;
        // For each term, consider the items rated by the user
        // skipping users without rates
        if (non_listed_users.find(user_pos) == non_listed_users.end()) {
            for (int term_pos = 0; term_pos < term_count; term_pos++) {
                float term_sum_value = 0.0;
                // Computing items references to a term
                for (int item_pos = 0; item_pos < items.size(); item_pos++) {
                    if ((utility_matrix[user_pos][item_pos] != 0)) {
                        item_count++;
                        term_sum_value +=
                                utility_matrix[user_pos][item_pos] * items_representations[item_pos][term_pos];
                    }
                }
                // If there are items rated by the user with this term push it to the representation
                if (item_count > 0) {
                    users_representations[user_idx][term_pos] = term_sum_value / item_count;
                }
                else {
                    users_representations[user_idx][term_pos] = 0;
                    zero_count++;
                }

            }
        }
        if (zero_count == term_count)
            missing_terms_user ++;
        DEBUG_ONLY(cout << "Representation " << user_pos << " / " << user_idx << " :" << vector2String<float>(users_representations[user_idx]) << endl
                    << "Missing users:" << missing_terms_user << " "
                    << "Checking users:" << non_listed_users.size() << " "
                    << missing_terms_user / static_cast<float>(target_users.size()) << "%"
                    << endl);
        user_idx ++;
    }
    return users_representations;
}

void ContentRecommender::compute_users_factors_matrix() {
    users_representation = compute_users_factors(items_representation);
}

void ContentRecommender::compute_similarities() {
    DEBUG_ONLY(cout << "Computing similarities" << endl);
    compute_similarities(items_representation, users_representation);
}

void ContentRecommender::clear_utility_matrix() {
    utility_matrix.clear();
}

void ContentRecommender::print_predictions() {
    cout << "UserId:ItemId,Prediction" << endl;
    for (size_t idx_target = 0; idx_target < targets_predictions.size(); idx_target ++ ) {
        cout <<  targets[idx_target][0] <<  ":" << targets[idx_target][1] << "," << targets_predictions[idx_target] << endl;
    }
}

void ContentRecommender::do_predictions() {
    cout << "UserId:ItemId,Prediction" << endl;
    size_t missing = 0;
    for (size_t idx_target = 0; idx_target < targets_positions.size(); idx_target ++ ) {
        size_t user_pos = targets_positions[idx_target].first;
        size_t item_pos = targets_positions[idx_target].second;
        float vote_prediction = 0.0f;
        size_t sim_vector_idx = distance(target_users.find(user_pos), target_users.end());
            float vote_sums = 0.0f;
            for (size_t n_idx =0; n_idx < NN; n_idx ++) {
                float n_sim = similar_items_NN[sim_vector_idx][n_idx].second;
                size_t n_pos = similar_items_NN[sim_vector_idx][n_idx].first;
                vote_sums += utility_matrix[user_pos][n_pos] * n_sim;
            }
            vote_prediction = vote_sums / static_cast<float>(NN);

        if (vote_prediction == 0) {
            vote_prediction = item_contents[item_pos].imdbRating;
            missing ++;
        }
        cout <<  targets[idx_target][0] <<  ":" << targets[idx_target][1] << "," << vote_prediction << endl;
    }
//    DEBUG_ONLY(cout << "Missing: " << missing  << " Targets: " << targets.size() << endl;)
}

void ContentRecommender::do_content_predictions() {
    do_content_predictions(items_representation, users_representation);
}
