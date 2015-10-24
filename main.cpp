//
// Created by Waner Miranda on 10/24/15.
//
#include <iostream>
#include <map>
#include <algorithm>
#include <unordered_map>
#include "StringUtils.h"
#include "CSVReader.h"
#include "ArrayUtils.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        cout << "usage: ./recommender content.csv ratings.csv targets.csv > output.csv";
        exit(1);
    }
}