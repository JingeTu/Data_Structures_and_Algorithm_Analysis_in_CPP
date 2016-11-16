//
// Created by 涂金戈 on 14/11/2016.
//

#include <iostream>
#include <vector>
#include "../Common_Tools/permutation.h"

template<typename Comparable>
void insertionSort(std::vector<Comparable> &a, int left, int right);

template<typename Comparable>
void quicksort(std::vector<Comparable> &a, int left, int right);

template<typename Comparable>
void quicksort(std::vector<Comparable> &a) {
    quicksort(a, 0, a.size() - 1);
}

template<typename Comparable>
const Comparable &median3(std::vector<Comparable> &a, int left, int right) {
    int center = (left + right) / 2;

    if (a[center] < a[left])
        std::swap(a[center], a[left]);
    if (a[right] < a[left])
        std::swap(a[right], a[left]);
    if (a[right] < a[center])
        std::swap(a[right], a[center]);

    std::swap(a[center], a[right - 1]);
    return a[right - 1];
}

template<typename Comparable>
void quicksort(std::vector<Comparable> &a, int left, int right) {
    if (left + 10 <= right) {
        const Comparable & pivot = median3(a, left, right);

        int i = left, j = right - 1;
        for (;;) {
            while (a[++i] < pivot);
            while (a[--j] > pivot);
            if (i < j)
                std::swap(a[i], a[j]);
            else
                break;
        }

        std::swap(a[i], a[right - 1]);

        quicksort(a, left, i - 1);
        quicksort(a, i + 1, right);
    }
    else
        insertionSort(a, left, right);
}

template<typename Comparable>
void insertionSort(std::vector<Comparable> &a, int left, int right) {
    int i, j;
    Comparable tmp;
    for (i = left + 1; i <= right; ++i) {
        tmp = std::move(a[i]);
        for (j = i; j > 0; --j) {
            if (tmp < a[j - 1])
                a[j] = std::move(a[j - 1]);
            else
                break;
        }
        a[j] = std::move(tmp);
    }
}

int main() {

    std::srand(std::time(0));

    const int SIZE = 50;
    int i;

    int *nums = Permutation3(SIZE);
    std::vector<int> nums_vec;
    nums_vec.reserve(SIZE);

    for (i = 0; i < SIZE; ++i)
        nums_vec.push_back(nums[i]);
    delete[] nums;

    quicksort(nums_vec);
//    insertionSort(nums_vec, 0, nums_vec.size() - 1);

    for (i = 0; i < SIZE; ++i)
        std::cout << nums_vec[i] << " ";
    std::cout << '\n';

    return 0;
}