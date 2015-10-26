//
// Created by Waner Miranda on 10/25/15.
//
#include "DebugUtils.h"
#include "RecommenderUtils.h"
#include "ArrayUtils.h"

void init_array(const unordered_map<string, size_t> &items, const unordered_map<string, size_t> &users,
                float **utility_matrix) {
    for (int user = 0; user < users.size(); user++) {
        for (int item = 0; item < items.size(); item++)
            utility_matrix[user][item] = FLOAT_NONE_VALUE;
    }
}


float **build_utility_matrix(const vector<vector<string>> &rows,
                             const unordered_map<string, size_t> &items,
                             const unordered_map<string, size_t> &users) {


    size_t row_count = users.size(), col_count = items.size();
    float **utility_matrix = alloc_2D_array<float>(row_count, col_count);
    init_array(items, users, utility_matrix);

    for (size_t index = 0; index < rows.size(); index++) {
        size_t user_pos = users.at(rows[index][0]);
        size_t item_pos = items.at(rows[index][1]);
        float vote = stod(rows[index][2]);

        utility_matrix[user_pos][item_pos] = vote;
    }

//    debug_print_array(row_count, col_count, utility_matrix);

    return utility_matrix;
}

void compute_stats_avg(vector<vector<float>> &stats) {// Overall average
    for (size_t index = 0; index < stats.size(); index++)
        if (stats[index][2] != -1){
            stats[index][1] = stats[index][2] / stats[index][0];
            // Zeroing the sum to a new average
            stats[index][2] = 0;
        }
}
