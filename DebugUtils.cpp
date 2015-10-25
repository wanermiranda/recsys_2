//
// Created by gorigan on 10/24/15.
//

#include "DebugUtils.h"

void debug_print_array(size_t N, float const *array) {
#ifdef DEBUG
    std::cout << '[';
    for (int col = 0; col < N; col++) {
        DEBUG_ONLY(std::cout << array[col] << ((col+1) < N? "," : ""));
    }
    std::cout << ']' <<std::endl;
#endif
}