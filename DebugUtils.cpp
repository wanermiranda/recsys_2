//
// Created by gorigan on 10/24/15.
//

#include "DebugUtils.h"
void debug_print_array(size_t M, size_t N, float *const *array)
{
#ifdef DEBUG
    std::cout << '[';
    for (size_t row = 0; row < M; row++)
        debug_print_array(N, array[row]);
    std::cout << ']' <<std::endl;
#endif
}
void debug_print_array(size_t N, float const *array) {
#ifdef DEBUG
    std::cout << '[';
    for (size_t col = 0; col < N; col++) {
        DEBUG_ONLY(std::cout << array[col] << ((col+1) < N? "," : ""));
    }
    std::cout << ']' <<std::endl;
#endif
}