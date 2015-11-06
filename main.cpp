//
// Created by Waner Miranda on 10/24/15.
//
#include <iostream>
#include <algorithm>

#include "ContentRecommender.h"
#include "DebugUtils.h"

using namespace std;



int main(int argc, char **argv) {
    if (argc < 4) {
        cout << "usage: ./recommender content.csv ratings.csv targets.csv > output.csv";
        exit(1);
    }

    ContentRecommender recommender;

    recommender.load_args(argv, argc);

    recommender.build_utility_matrix();

    recommender.build_representations();

    recommender.compute_users_factors_matrix();

    recommender.do_content_predictions();

    recommender.print_predictions();

    DEBUG_ONLY(cout << "Finished " << endl);

    exit(0);
}