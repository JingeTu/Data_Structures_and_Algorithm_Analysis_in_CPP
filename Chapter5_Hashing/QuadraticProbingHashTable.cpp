//
// Created by 涂金戈 on 09/11/2016.
//

#include "QuadraticProbingHashTable.h"

template<typename HashedObj>
QuadraticProbingHashTable<HashedObj>::QuadraticProbingHashTable(int size): array(nextPrime(size)) {
    makeEmpty();
}

template<typename HashedObj>
void QuadraticProbingHashTable<HashedObj>::makeEmpty() {
    currentSize = 0;
    for (auto &entry : array)
        entry.info = EMPTY;
}

template<typename HashedObj>
bool QuadraticProbingHashTable<HashedObj>::isEmpty() {
    return currentSize == 0;
}

template<typename HashedObj>
bool QuadraticProbingHashTable<HashedObj>::contains(const HashedObj &x) const {
    return isActive(findPos(x));
}

template<typename HashedObj>
int QuadraticProbingHashTable<HashedObj>::findPos(const HashedObj &x) const {
    int currentPos = myhash(x);
    int offset = 1;

    while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
        currentPos += offset;
        offset += 2;

        if (currentPos >= array.size()) {
            currentPos -= array.size();
        }
    }

    return currentPos;
}

template<typename HashedObj>
bool QuadraticProbingHashTable<HashedObj>::isActive(int currentPos) const {
    return array[currentPos].info == ACTIVE;
}

template<typename HashedObj>
bool QuadraticProbingHashTable<HashedObj>::insert(const HashedObj &x) {
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return false;

    array[currentPos].element = x;
    array[currentPos].info = ACTIVE;

    if (++currentSize > array.size() / 2) { // add currentSize
        rehash();
    }

    return true;
}

template<typename HashedObj>
bool QuadraticProbingHashTable<HashedObj>::insert(HashedObj &&x) {
    return insert(std::move(x));
}

template<typename HashedObj>
bool QuadraticProbingHashTable<HashedObj>::remove(const HashedObj &x) {
    int currentPos = findPos(x);
    if (!isActive(currentPos))
        return false;

    array[currentPos].info = DELETED;
    // do not change currentSize here, it is lazy deletion
    return true;
}

template<typename HashedObj>
size_t QuadraticProbingHashTable<HashedObj>::nextPrime(size_t N) {
    if (N % 2 == 0)
        ++N;
    for (;; N += 2) {
        bool isPrime = true;
        for (size_t i = 3; i * i < N; ++i) {
            if (N % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime)
            return N;
    }
}

template<typename HashedObj>
void QuadraticProbingHashTable<HashedObj>::rehash() {
    std::vector<HashEntry> oldArray = array;

    array.resize(nextPrime(2 * oldArray.size()));
    for (auto &entry : array)
        entry.info = EMPTY;

    currentSize = 0;
    for (auto &entry : oldArray)
        if (entry.info == ACTIVE)
            insert(std::move(entry.element));
}

template<typename HashedObj>
size_t QuadraticProbingHashTable<HashedObj>::myhash(const HashedObj &x) const {
    static hash<HashedObj> hf;
    return hf(x) % array.size();
}