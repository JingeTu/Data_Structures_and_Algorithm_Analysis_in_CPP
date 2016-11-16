//
// Created by 涂金戈 on 11/11/2016.
//

#include <iostream>
#include "BinaryHeap.h"
#include "../Common_Tools/permutation.h"

int main() {

    BinaryHeap<int> bh;

    std::srand(std::time(0));

    int *nums = Permutation3(10);

    for (int i = 0; i < 10; ++i) {
        bh.insert(nums[i]);
    }

    delete[] nums;

    bh.printHeap();

    bh.deleteMin();

    bh.printHeap();

    return 0;
}