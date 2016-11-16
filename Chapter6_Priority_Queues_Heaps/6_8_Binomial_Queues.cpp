//
// Created by 涂金戈 on 11/11/2016.
//

#include "BinomialQueue.h"
#include <iostream>
#include "../Common_Tools/permutation.h"


int main() {

    BinomialQueue<int> bq;

    std::srand(std::time(0));

    int *nums = Permutation3(10);

    for (int i = 0; i < 10; ++i) {
        bq.insert(nums[i]);
    }
    delete[] nums;

    return 0;
}