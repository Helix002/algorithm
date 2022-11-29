#include "minunit.h"
#include "sort_c.h"
#include "sort_cxx_wrapper.h"

#include <stdio.h>

void (*sort)(int*, int);
void (*sort_arr[])(int*, int) = {
    bubble,
    select,
    insert,
    shell,
    merge,
    quick,
    heap,
    count,
    bucket,
    radix 
};

static int array_compare(int src[], int dst[], int size)
{
    for (int i = 0; i < size; ++i) {
        if (src[i] != dst[i]) {
            return -1;
        }
    }
    return 0;
}

static int array_print(int src[], int size)
{
    for (int i = 0; i < size; ++i) {
        printf("%d ", src[i]);
    }
    printf("\n");
    return 0;
}


int tests_run = 0;

static int test_case_common(int array[], int arr_len, int result[], int res_len)
{
    if (arr_len != res_len) {
        printf("array's size is not equal");
        return -1;
    }

    printf("RUN TESTCASE:\n");
    
    printf("Input sequence:\t");
    array_print(array, arr_len);

    sort(array, arr_len);
    
    printf("Output sequence:\t");
    array_print(array, arr_len);

    int res = array_compare(array, result, res_len);
    return res;
}

static char * test_case_1() {
    int array[] = {21, 12, 32, 43, 8, 16, 25, 39, 29, 50, 32, 48};
    int result[] = {8, 12, 16, 21, 25, 29, 32, 32, 39, 43, 48, 50};

    
    int res = test_case_common(array, sizeof(array)/sizeof(array[0]),
                                result, sizeof(result)/sizeof(result[0]));

    mu_assert("test_case_1 failed", 0 == res);
    return 0;
}

static char * test_case_2() {
    int array[] = {32, 7, 16, 15, 38, 10, 4, 18, 20, 9, 12, 40, 44};
    int result[] = {4, 7, 9, 10, 12, 15, 16, 18, 20, 32, 38, 40, 44};

    int res = test_case_common(array, sizeof(array)/sizeof(array[0]),
                                result, sizeof(result)/sizeof(result[0]));

    mu_assert("test_case_2 failed", 0 == res);
    return 0;
}

static char * test_case_3() {
    int array[] = {46, 17, 11, 3, 16, 39, 3, 40, 19, 4, 18, 46};
    int result[] = {3, 3, 4, 11, 16, 17, 18, 19, 39, 40, 46, 46};

    int res = test_case_common(array, sizeof(array)/sizeof(array[0]),
                                result, sizeof(result)/sizeof(result[0]));

    mu_assert("test_case_3 failed", 0 == res);
    return 0;
}

static char *all_tests() {

    for (int i = 0; i < sizeof(sort_arr)/sizeof(sort_arr[0]); ++i) {
        if (NULL == sort_arr[i]) {
            continue;
        } else {
            sort = sort_arr[i];
        }

        mu_run_test(test_case_1);
        mu_run_test(test_case_2);
        mu_run_test(test_case_3);
    }
    return 0;
}

static char *single_tests() {

    sort = heap;
    mu_run_test(test_case_1);
    mu_run_test(test_case_2);
    mu_run_test(test_case_3);

    return 0;
}

int main(int argc, char **argv) {
    char *result = single_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}