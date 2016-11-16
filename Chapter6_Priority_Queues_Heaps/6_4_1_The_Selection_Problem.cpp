//
// Created by 涂金戈 on 11/11/2016.
//

#include "BinaryHeap.h"
#include <vector>
#include <iostream>

template<typename Comparable>
Comparable ThekthSmallestElement_6A(const std::vector<Comparable> &elements, const int &k) {
    BinaryHeap<Comparable> bh(elements);

    for (int i = 0; i < k - 1; ++i) {
        bh.deleteMin();
    }

    Comparable ret;
    bh.deleteMin(ret);

    return ret;
}

template<typename Comparable>
Comparable ThekthLargestElement_6B(const std::vector<Comparable> &elements, const int &k) {
    BinaryHeap<Comparable> bh(k);
    int i;

    for (i = 0; i < k; ++i) {
        bh.insert(elements[i]);
    }

    for (i = k; i < elements.size(); ++i)
        if (bh.findMin() < elements[i]) {
            bh.deleteMin();
            bh.insert(elements[i]);
        }

    Comparable ret;
    bh.deleteMin(ret);

    return ret;
}

int main() {

    std::vector<int> nums(20);

    for (int i = 1; i < 20 + 1; ++i) {
        nums[i - 1] = i;
    }

    std::cout << ThekthSmallestElement_6A(nums, 10) << std::endl;
    std::cout << ThekthLargestElement_6B(nums, 10) << std::endl;

    return 0;
}