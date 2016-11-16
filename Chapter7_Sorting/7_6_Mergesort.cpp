//
// Created by 涂金戈 on 13/11/2016.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include "../Common_Tools/permutation.h"

template<typename Comparable>
void mergeSort(std::vector<Comparable> &a, std::vector<Comparable> &tmpArray, int left, int right);

template<typename Comparable>
void merge(std::vector<Comparable> &a, std::vector<Comparable> &tmpArray, int leftPos, int rightPos, int rightEnd);

template<typename Comparable>
void mergeSort(std::vector<Comparable> &a) {
    std::vector<Comparable> tmpArray(a.size());

    mergeSort(a, tmpArray, 0, a.size() - 1);
}

template<typename Comparable>
void mergeSort(std::vector<Comparable> &a, std::vector<Comparable> &tmpArray, int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        mergeSort(a, tmpArray, left, center);
        mergeSort(a, tmpArray, center + 1, right);
        merge(a, tmpArray, left, center + 1, right);
    }
}

template<typename Comparable>
void merge(std::vector<Comparable> &a, std::vector<Comparable> &tmpArray, int leftPos, int rightPos, int rightEnd) {
    int leftIt = leftPos;
    int rightIt = rightPos;
    int tmpIt = leftPos;

    while (leftIt <= rightPos - 1 && rightIt <= rightEnd) {
        if (a[leftIt] < a[rightIt])
            tmpArray[tmpIt++] = std::move(a[leftIt++]);
        else
            tmpArray[tmpIt++] = std::move(a[rightIt++]);
    }

    while (leftIt <= rightPos - 1)
        tmpArray[tmpIt++] = std::move(a[leftIt++]);

    while (rightIt <= rightEnd)
        tmpArray[tmpIt++] = std::move(a[rightIt++]);

    // copy tmpArray to a
    for (tmpIt = leftPos; tmpIt <= rightEnd; ++tmpIt)
        a[tmpIt] = std::move(tmpArray[tmpIt]);
}


int main() {

    std::srand(std::time(0));

    const int SIZE = 15;
    int i;

    int* nums = Permutation3(SIZE);
    std::vector<int> nums_vec;
    nums_vec.reserve(SIZE);

    for (i = 0; i < SIZE; ++i)
        nums_vec.push_back(nums[i]);

    delete[] nums;

    mergeSort(nums_vec);

    for (i = 0; i < SIZE; ++i)
        std::cout << nums_vec[i] << " ";
    std::cout << "\n";

    return 0;
}