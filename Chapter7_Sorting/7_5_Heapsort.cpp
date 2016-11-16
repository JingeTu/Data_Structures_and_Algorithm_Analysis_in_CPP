//
// Created by 涂金戈 on 14/11/2016.
//

#include <iostream>
#include <vector>
#include "../Common_Tools/permutation.h"

template<typename Comparable>
void percDown(std::vector<Comparable> &a, int i, int n);

template<typename Comparable>
void heapsort(std::vector<Comparable> &a) {
    int i;
    for (i = a.size() / 2 - 1; i >= 0; --i)
        percDown(a, i, a.size());
    for (i = a.size() - 1; i > 0; --i) {
        std::swap(a[0], a[i]);
        percDown(a, 0, i);
    }
}

inline int leftChild(int i) {
    return i * 2 + 1;
}

template<typename Comparable>
void percDown(std::vector<Comparable> &a, int i, int n) {
    int child;
    Comparable tmp = std::move(a[i]);

    for (; leftChild(i) < n; i = child) {
        child = leftChild(i);
        if (child + 1 < n && a[child] < a[child + 1])
            ++child;
        if (tmp < a[child])
            a[i] = std::move(a[child]);
        else
            break;
    }

    a[i] = std::move(tmp);
}

int main() {

    std::srand(std::time(0));

    const int SIZE = 20;
    int i;

    int *nums = Permutation3(SIZE);
    std::vector<int> nums_vec;
    nums_vec.reserve(SIZE);

    for (i = 0; i < SIZE; ++i)
        nums_vec.push_back(nums[i]);
    delete[] nums;

    heapsort(nums_vec);

    for (i = 0; i < nums_vec.size(); i++)
        std::cout << nums_vec[i] << " ";
    std::cout << "\n";

    return 0;
}