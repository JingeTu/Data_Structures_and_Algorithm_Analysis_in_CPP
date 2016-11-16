//
// Created by 涂金戈 on 12/11/2016.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include "../Common_Tools/permutation.h"

template<typename Iterator, typename Comparator>
void insertionSort(const Iterator &begin, const Iterator &end, Comparator lessThan);

template<typename Iterator>
void insertionSort(const Iterator &begin, const Iterator &end) {
    insertionSort(begin, end, std::less<decltype(*begin)> {});
}

template<typename Iterator, typename Comparator>
void insertionSort(const Iterator &begin, const Iterator &end, Comparator lessThan) {
    if (begin == end)
        return;

    Iterator j, p;
    for (p = begin; p != end; ++p) {
        auto tmp = std::move(*p);
        for (j = p; j != begin && tmp < *(j - 1); --j)
            *j = std::move(*(j - 1));
        *j = std::move(tmp);
    }
}

int main() {

    std::srand(std::time(0));

    std::vector<int> nums_vec(10);
    int *nums = Permutation3(10);

    for (int i = 0; i < 10; ++i)
        nums_vec[i] = std::move(nums[i]);

    delete[] nums;

    insertionSort(nums_vec.begin(), nums_vec.end());

    for (int i = 0; i < nums_vec.size(); ++i)
        std::cout << nums_vec[i] << " ";

    return 0;
}