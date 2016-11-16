//
// Created by 涂金戈 on 11/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_BINARYHEAP_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_BINARYHEAP_H

#include <vector>

template<typename Comparable>
class BinaryHeap {
public:
    explicit BinaryHeap(int capacity = 100);

    explicit BinaryHeap(const std::vector<Comparable> &items);

    bool isEmpty() const;

    const Comparable &findMin() const;

    void insert(const Comparable &x);

    void insert(Comparable &&x);

    void deleteMin();

    void deleteMin(Comparable &minItem);

    void makeEmpty();

    void printHeap();

private:
    int currentSize;
    std::vector<Comparable> array;

    void buildHeap();

    void percolateDown(int hole);
};

#include "BinaryHeap.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_BINARYHEAP_H
