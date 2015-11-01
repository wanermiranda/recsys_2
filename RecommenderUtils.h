//
// Created by Waner Miranda on 10/25/15.
//

#ifndef TP1_RECSYS_RECOMMENDERUTILS_H
#define TP1_RECSYS_RECOMMENDERUTILS_H
#include "Constants.h"
#include <map>
#include <string>
#include <stddef.h>
#include <unordered_map>

using namespace std;

float **build_utility_matrix(const vector<vector<string>> &rows,
                             const unordered_map<string, size_t> &items,
                             const unordered_map<string, size_t> &users);

void init_utility_matrix(const unordered_map<string, size_t> &items, const unordered_map<string, size_t> &users,
                         float **utility_matrix);


void compute_stats_avg(vector<vector<float>> &stats);
#endif //TP1_RECSYS_RECOMMENDERUTILS_H
