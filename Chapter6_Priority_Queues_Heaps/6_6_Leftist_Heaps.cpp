//
// Created by 涂金戈 on 11/11/2016.
//

#include <iostream>
#include "LeftistHeap.h"
#include "../Common_Tools/permutation.h"

int main() {

    LeftistHeap<int> lh;

    std::srand(std::time(0));

    int *nums = Permutation3(10);

    std::cout << "Insert sequence: ";

    for (int i = 0; i < 10; ++i) {
        std::cout << nums[i] << ' ';
        lh.insert(nums[i]);
    }
    std::cout << std::endl;

    lh.printHeap();

    delete[] nums;

    return 0;
}