//
// Created by 涂金戈 on 13/11/2016.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include "../Common_Tools/permutation.h"

template<typename Comparable>
void SORT(std::vector<Comparable> &items) {
    if (items.size() > 1) {
        std::vector<Comparable> smaller;
        std::vector<Comparable> larger;
        std::vector<Comparable> same;

        Comparable pivot = items[items.size() / 2];

        for (Comparable &i : items) {
            if (i < pivot)
                smaller.push_back(i);
            else if (i > pivot)
                larger.push_back(i);
            else
                same.push_back(i);
        }

        SORT(smaller);
        SORT(larger);

        std::move(smaller.begin(), smaller.end(), items.begin());
        std::move(same.begin(), same.end(), items.begin() + smaller.size());
        std::move(larger.begin(), larger.end(), items.begin() + smaller.size() + same.size());
    }
}

int main() {

    std::srand(std::time(0));

    const int SIZE = 15;
    int i;

    int *nums = Permutation3(SIZE);
    std::vector<int> nums_vec;
    nums_vec.reserve(SIZE);

    for (i = 0; i < SIZE; ++i)
        nums_vec.push_back(nums[i]);

    delete[] nums;

    SORT(nums_vec);

    for (i = 0; i < SIZE; ++i)
        std::cout << nums_vec[i] << " ";
    std::cout << "\n";

    return 0;
}