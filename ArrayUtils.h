//
// Created by Waner Miranda on 10/2/15.
//

#ifndef TP1_RECSYS_ARRAYUTILS_H
#define TP1_RECSYS_ARRAYUTILS_H

#include "Constants.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename T>
string vector2String(vector<T> vector1) {
    string output;
    output  = "[ ";
    for (auto value: vector1) output += value + ' ';
    output  += "] ";
    return output;
}

template <typename T> T **alloc_2D_array(size_t M, size_t N) {
    T **array;
    array = (T **)malloc(sizeof (*array) * M);
    if (array)
    {

        for (size_t i = 0; i < M; i++)
        {
            array[i] = (T *)malloc(N * (sizeof *array[i]));
        }
    }
    return array;
}
template <typename T> T *alloc_1D_array(size_t N) {
    T *array = (T*)malloc(sizeof (T) * N);
    return array;
}

template <typename T>
T find_by_value(std::vector<T> vector, T value){
    auto it = std::find(vector.begin(), vector.end(), value);
    if (it == vector.end())
        exit(42);
    return it - vector.begin();
}


#endif //TP1_RECSYS_ARRAYUTILS_H