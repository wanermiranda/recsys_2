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
#include <sstream>
#include <unordered_map>

using namespace std;

template <typename K, typename V>
void increment_insert_map(unordered_map<K, set<V>> &map, K key, V value) {
    auto it = map.find(key);
    if(it != map.end())
        it->second.insert(value);
    else {
        set<V> values = {value};
        map.insert({key, values});
    }
}

template <typename T>
T **alloc2dArray( size_t nRows, size_t nCols)
{
    T **dynamicArray;

    dynamicArray = new T*[nRows];
    for( int i = 0 ; i < nRows ; i++ )
        dynamicArray[i] = new T [nCols];

    return dynamicArray;
}

template <typename T>
void free2DArray(T** dynamicArray, size_t nRows)
    {
        for( int i = 0 ; i < nRows ; i++ )
            delete[]  dynamicArray[i];
        delete dynamicArray;
    }

template<typename T>
string vector2String(const vector<T> &vector1) {
    stringstream output;
    output  << "[ ";
    for (auto value: vector1) output << value  << ' ';
    output  << "] ";
    return output.str();
}

template<typename T1, typename T2>
string vectorPairs2String(const vector<pair<T1, T2>> &vector1) {
    stringstream output;
    output  << "[ ";
    for (auto value: vector1) output << value.first  << ':' << value.second << ' ';
    output  << "] ";
    return output.str();
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
T find_by_value(const std::vector<T> &vector, T value){
    auto it = std::find(vector.begin(), vector.end(), value);
    if (it == vector.end())
        exit(42);
    return it - vector.begin();
}

template <typename T> void append_vectors(std::vector<T> &target, const std::vector<T> &source){
    if (target.empty())
    {
        target = source;
    }
    else
    {
        target.reserve(target.size() + source.size());
        std::copy(std::begin(source), std::end(source), std::back_inserter(target));
    }
}
#endif //TP1_RECSYS_ARRAYUTILS_H