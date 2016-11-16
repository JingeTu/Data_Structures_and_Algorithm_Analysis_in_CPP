//
// Created by 涂金戈 on 12/11/2016.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include "../Common_Tools/permutation.h"

template<typename Comparable>
void shellsort(std::vector<Comparable> &a) {
    int i, j;
    for (int gap = a.size() / 2; gap > 0; gap /= 2)
        for (i = gap; i < a.size(); ++i) {
            Comparable tmp = std::move(a[i]);
//            for (j = i; j > 0 && tmp < a[j - gap]; j -= gap) // if j < gap, then a[j - gap] access invalid.
            for (j = i; j >= gap && tmp < a[j - gap]; j -= gap)
                a[j] = std::move(a[j - gap]);
            a[j] = std::move(tmp);
        }
}

int main() {

    std::srand(std::time(0));

    const int SIZE = 30;

    int *nums = Permutation3(SIZE);
    std::vector<int> nums_vec;
    nums_vec.reserve(SIZE);

    for (int i = 0; i < SIZE; ++i)
        nums_vec.push_back(nums[i]);

    delete[] nums;

    shellsort(nums_vec);

    for (int i = 0; i < nums_vec.size(); ++i)
        std::cout << nums_vec[i] << " ";
    std::cout << '\n';

    return 0;
}
