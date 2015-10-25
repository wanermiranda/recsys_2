//
// Created by gorigan on 10/24/15.
//

#ifndef TP1_RECSYS_DEBUGUTILS_H
#define TP1_RECSYS_DEBUGUTILS_H
#include "Constants.h"
#include <iostream>
#include <stddef.h>
#include <vector>
#ifdef DEBUG
#define DEBUG_STDERR(x) (std::cerr << (x))
#define DEBUG_ONLY(x) x
//... etc
#else
#define DEBUG_STDERR(x)
#define DEBUG_ONLY(x)
//... etc
#endif
using namespace std;
void debug_print_array(size_t M, size_t N, float *const *array);

void debug_print_array(size_t N, float const *array);

#endif //TP1_RECSYS_DEBUGUTILS_H
