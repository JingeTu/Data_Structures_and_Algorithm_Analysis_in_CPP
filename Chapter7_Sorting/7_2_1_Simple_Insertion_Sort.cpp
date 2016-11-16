//
// Created by 涂金戈 on 12/11/2016.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include "../Common_Tools/permutation.h"

template<typename Comparable>
void insertionSort(std::vector<Comparable> &a) {
    int j, p;
    for (p = 1; p < a.size(); ++p) {
        Comparable tmp = std::move(a[p]);

        for (j = p; j > 0 && tmp < a[j - 1]; --j) {
            a[j] = std::move(a[j - 1]);
        }
        a[j] = std::move(tmp);
    }
}

int main() {

    std::srand(std::time(0));

    std::vector<int> nums_vec(10);
    int *nums = Permutation3(10);

    for (int i = 0; i < 10; ++i)
        nums_vec[i] = std::move(nums[i]);

    delete[] nums;

    insertionSort(nums_vec);

    for (int i = 0; i < nums_vec.size(); ++i)
        std::cout << nums_vec[i] << " ";

    std::cout << std::endl;

    return 0;
}