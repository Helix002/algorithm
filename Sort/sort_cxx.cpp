#include "sort_cxx.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

void bucket_sort(int array[], int size)
{
    int max, min;
    max = min = array[0];

    for (auto i = 0; i < size; ++i) {
        array[i] > max ? max = array[i]: 0;
        array[i] < min ? min = array[i]: 0;
    }

    int interval = (max - min) / size + 1;

    std::vector<std::vector<int> *> buckets;
    for (auto i = 0; i < size + 1; ++i) {
        std::vector<int> * v = new std::vector<int>();
        buckets.push_back(v);
    }

    for (auto i = 0; i < size; ++i) {
        int index = array[i] / interval;
        buckets.at(index)->push_back(array[i]);
    }

    int index = 0;
    for (auto i : buckets) {
        if (i->empty()) {
            continue;
        }

        std::sort(i->begin(), i->end());

        for (auto j : *i) {
            array[index++] = j;
        }
    }

    for (auto iter = buckets.begin(); iter != buckets.end(); ++iter) {
        if ((*iter) != nullptr) {
            delete (*iter);
            *iter = nullptr;
        }
    }
}


void radix_sort(int array[], int size)
{
    const int radix = 10;

    std::vector<std::vector<int> *> buckets;
    for (auto i = 0; i < radix; ++i) {
        std::vector<int> * v = new std::vector<int>();
        buckets.push_back(v);
    }

    int max = array[0];
    for (auto i = 0; i < size; ++i) {
        array[i] > max ? max = array[i] : 0;
    }

    for (int count = 0; max != 0; ++count, max /= radix) {

        for (auto i = 0; i < size; ++i) {

            int element = array[i];
            for (int k = count; k > 0; --k) {
                element /= radix;
            }
            int index = element % radix;

            buckets.at(index)->push_back(array[i]);
        }

        int index = 0;
        for (auto i : buckets) {
            if (i->empty()) {
                continue;
            }

            for (auto j : *i) {
                array[index++] = j;  /* 回写 */
            }

            i->clear(); /* 清空桶*/
        }
    }

    /* 释放空间 */
    for (auto iter = buckets.begin(); iter != buckets.end(); ++iter) {
        if ((*iter) != nullptr) {
            delete (*iter);
            *iter = nullptr;
        }
    }

}