//
// Created by gorigan on 10/6/15.
//

#ifndef TP1_RECSYS_DISTANCES_H
#define TP1_RECSYS_DISTANCES_H

#include <iostream>
#include <vector>

using namespace std;

auto distance_comparer = [](const std::pair<float, size_t> &a, const std::pair<float, size_t> &b) {
    return (a.first < b.first && a.second != b.second);
};


float vector_normconst (vector<float> &vector1);

float vector_norm(const vector<float> &vector1, size_t sz);

float dot_product(const vector<float> &vector1, const vector<float> &vector2);

float dot_product(float *vector1, float *vector2, size_t sz);

float cosine_distance(const float *vector1, const float *vector2, size_t size_cols);

float manhattan_distance(const vector<float> vector1, const vector<float> vector2);

#endif //TP1_RECSYS_DISTANCES_H
