#include "sort.h"

void bubble(int array[], int size)
{
    for (int i = 0; i < size - 1; ++i) {
        bool is_sorted = true;
        for (int j = 0; j < size - 1 - i; ++j) {
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;

                is_sorted = false;
            }
        }
        if (is_sorted) {
            break;
        }
    }
}

void select(int array[], int size)
{
    for (int i = 0; i < size - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < size; ++j) {
            if (array[j] < array[min]) {
                min = j;
            }
        }

        int temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}

void insert(int array[], int size)
{
    for (int i = 1; i < size; ++i) {
        int temp = array[i];

        int index = i - 1;
        while (index >= 0) {
            if(temp < array[index]) {
                array[index+1] = array[index];
            } else {
                break;
            }
            index--;
        }
        array[index+1] = temp;
    }
}

void shell(int array[], int size)
{
    /* Insert is a special case of the shell when stepping = 1*/
    int stepping = 1;

    while(stepping < size)
        stepping = stepping * 3 + 1;

    while (stepping > 0) {
        for (int i = stepping; i < size; ++i) {
            int temp = array[i];

            int index = i - stepping;
            while (index >= 0) {
                if(temp < array[index]) {
                    array[index+stepping] = array[index];
                } else {
                    break;
                }
                index -= stepping;
            }
            array[index+stepping] = temp;
        }
        stepping /= 3;
    }
}

static void merge_conquer(int array[], int tmp_arr[], int start, int mid, int end)
{
    for (int i = start; i <= end; ++i) {
        tmp_arr[i] = array[i];
    }

    int left = start;
    int right = mid + 1;

    for (int i = start; i <= end; i++) { /* 类似于双指针 */
        if(left > mid) {
            array[i] = tmp_arr[right++];
        } else if (right > end) {
            array[i] = tmp_arr[left++];
        } else if (tmp_arr[left] <= tmp_arr[right]) { /* 不稳定， 相等时优先插入左侧的值 */
            array[i] = tmp_arr[left++];
        } else if (tmp_arr[right] < tmp_arr[left]) {
            array[i] = tmp_arr[right++];
        }
    }
}

static void merge_divide(int array[], int tmp_arr[], int start, int end)
{
    if(start >= end) {
        return;
    }

    int mid = start + (end - start) / 2;

    merge_divide(array, tmp_arr, start, mid);
    merge_divide(array, tmp_arr, mid + 1, end);

    merge_conquer(array, tmp_arr, start, mid, end);
}

void merge(int array[], int size)
{
    int* tmp_arr = (int*) malloc(sizeof(int) *size);
    merge_divide(array, tmp_arr, 0, size - 1); /* 注意这里传入的是下标 */

    free(tmp_arr);
    tmp_arr = NULL;
}

static int quick_conquer(int array[], int start, int end)
{
    int left = start;
    int right = end;

    while (1)
    {
        for(; left!=right && array[left] <= array[end]; left++);
        for(; left!=right && array[right] > array[end]; right--);

        if (left >= right)
            break;
        
        int temp = array[left];
        array[left] = array[right];
        array[right] = temp;
    }
    
    int temp = array[end];
    array[end] = array[right];
    array[right] = temp;

    return right;
}

static void quick_divide(int array[], int start, int end)
{
    if (start >= end) {
        return;
    }

    int pos = quick_conquer(array, start, end);

    quick_divide(array, start, pos - 1); /* pos位置的值已经确定了 */
    quick_divide(array, pos + 1, end);
}

void quick(int array[], int size)
{
    quick_divide(array, 0, size - 1);
}




void count(int array[], int size)
{
    int max = array[0];
    for (int i = 0; i < size; ++i) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    int *count_arr = (int *)calloc(max + 1, sizeof(int));

    for (int i = 0; i < size; ++i) {
        count_arr[array[i]]++;
    }

    int j = 0;
    for (int k = 0; k <= max; ++k) {
        while (count_arr[k] > 0) {
            array[j++] = k;
            count_arr[k]--;
        }
    }    

    free(count_arr);
    count_arr = NULL;

}

