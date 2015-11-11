//
// Created by Waner Miranda on 10/25/15.
//
#include "DebugUtils.h"
#include "RecommenderUtils.h"
#include "ArrayUtils.h"

void init_utility_matrix(const unordered_map<string, size_t> &items, const unordered_map<string, size_t> &users,
                         vector<vector<float>>utility_matrix) {
    for (size_t user = 0; user < users.size(); user++) {
        for (size_t item = 0; item < items.size(); item++)
            utility_matrix[user][item] = FLOAT_NONE_VALUE;
    }
}

void compute_stats_avg(vector<vector<float>> &stats) {// Overall average
    for (size_t index = 0; index < stats.size(); index++)
        if (stats[index][2] != -1){
            stats[index][1] = stats[index][2] / stats[index][0];
            // Zeroing the sum to a new average
            stats[index][2] = 0;
        }
}
