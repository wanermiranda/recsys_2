//
// Created by gorigan on 10/24/15.
//

#ifndef TP1_RECSYS_READINPUTS_H
#define TP1_RECSYS_READINPUTS_H
#include "Constants.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

void read_targets(char *filename, unordered_map<string, size_t> &items, unordered_map<string, size_t> &users,
                  vector<vector<float>> &items_stats, vector<vector<float>> &users_stats,
                  vector<vector<string>> &targets,
                  vector<size_t> &target_users);

void read_ratings(const char *filename, unordered_map<string, size_t> &items, unordered_map<string, size_t> &users,
                  vector<vector<string>> &rows, vector<vector<float>> &items_stats,
                  vector<vector<float>> &users_stats);
#endif //TP1_RECSYS_READINPUTS_H
