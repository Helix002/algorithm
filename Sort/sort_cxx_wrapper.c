#include "sort_cxx_wrapper.h"
#include "sort_cxx.hpp"

#ifdef __cplusplus
extern "C" {
#endif



void bucket(int array[], int size)
{
    bucket_sort(array, size);
}

void radix(int array[], int size)
{
    radix_sort(array, size);
}

#ifdef __cplusplus
}
#endif


