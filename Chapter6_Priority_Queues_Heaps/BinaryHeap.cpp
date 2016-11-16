//
// Created by 涂金戈 on 11/11/2016.
//

#include "BinaryHeap.h"

template<typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(int capacity): array(capacity), currentSize{0} {

}

template<typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(const std::vector<Comparable> &items): array(items.size() + 1),
                                                                          currentSize{(int)items.size()} {
    for (int i = 0; i < items.size(); ++i)
        array[i + 1] = items[i];
    buildHeap();
}

template<typename Comparable>
bool BinaryHeap<Comparable>::isEmpty() const {
    return currentSize == 0;
}

template<typename Comparable>
void BinaryHeap<Comparable>::makeEmpty() {
    currentSize = 0;
}

template<typename Comparable>
const Comparable &BinaryHeap<Comparable>::findMin() const {
    return array[1];
}

template<typename Comparable>
void BinaryHeap<Comparable>::insert(const Comparable &x) {
    if (currentSize + 1 == array.size())
        array.resize(array.size() * 2);

    int hole = ++currentSize;
    Comparable copy = x;

    array[0] = std::move(copy);
    for (; x < array[hole / 2]; hole /= 2) {
        array[hole] = std::move(array[hole / 2]);
    }
    array[hole] = std::move(array[0]);
}

template<typename Comparable>
void BinaryHeap<Comparable>::insert(Comparable &&x) {
    insert(std::move(x));
}

template<typename Comparable>
void BinaryHeap<Comparable>::deleteMin() {
    if (isEmpty())
        return;

    array[1] = std::move(array[currentSize--]);
    percolateDown(1);
}

template<typename Comparable>
void BinaryHeap<Comparable>::deleteMin(Comparable &minItem) {
    if (isEmpty())
        return;

    minItem = std::move(array[1]);
    array[1] = std::move(array[currentSize--]);
    percolateDown(1);
}

template<typename Comparable>
void BinaryHeap<Comparable>::percolateDown(int hole) {
    Comparable copy = std::move(array[hole]);
    int smallerIndex;

    while (hole * 2 <= currentSize) {
        smallerIndex = hole * 2;
        if (smallerIndex < currentSize && array[smallerIndex + 1] < array[smallerIndex])
            ++smallerIndex;
        if (copy > array[smallerIndex])
            array[hole] = std::move(array[smallerIndex]);
        else // remember breaking to save time
            break;
        hole = smallerIndex;
    }
    array[hole] = std::move(copy);
}

template<typename Comparable>
void BinaryHeap<Comparable>::buildHeap() {
    for (int i = currentSize / 2; i > 0; --i)
        percolateDown(i);
}

template<typename Comparable>
void BinaryHeap<Comparable>::printHeap() {
    for (int i = 1; i <= currentSize; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}
