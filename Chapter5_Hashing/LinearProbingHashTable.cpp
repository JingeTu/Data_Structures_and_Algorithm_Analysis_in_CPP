//
// Created by 涂金戈 on 09/11/2016.
//

#include "LinearProbingHashTable.h"

template<typename HashedObj>
LinearProbingHashTable<HashedObj>::LinearProbingHashTable(int size): array(nextPrime(size)) {
    makeEmpty();
}

template<typename HashedObj>
bool LinearProbingHashTable<HashedObj>::contains(const HashedObj &x) const {
    return isActive(findPos(x));
}

template<typename HashedObj>
void LinearProbingHashTable<HashedObj>::makeEmpty() {
    currentSize = 0;
    for (auto &entry : array)
        entry.info = EMPTY;
}

template<typename HashedObj>
bool LinearProbingHashTable<HashedObj>::insert(const HashedObj &x) {
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return false;

    array[currentPos].info = ACTIVE;
    array[currentPos].element = x;

    if (++currentSize >= array.size() / 2)
        rehash();

    return true;
}

template<typename HashedObj>
bool LinearProbingHashTable<HashedObj>::insert(HashedObj &&x) {
    return insert(std::move(x));
}

template<typename HashedObj>
bool LinearProbingHashTable<HashedObj>::remove(const HashedObj &x) {
    int currentPos = findPos(x);
    if (!isActive(currentPos))
        return false;

    array[currentPos].info = EMPTY;

    return true;
}

template<typename HashedObj>
int LinearProbingHashTable<HashedObj>::findPos(const HashedObj &x) const {
    int currentPos = myhash(x);
    int offset = 1;

    while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
        currentPos += offset;
        ++offset;

        if (currentPos >= array.size())
            currentPos -= array.size();
    }

    return currentPos;
}

template<typename HashedObj>
int LinearProbingHashTable<HashedObj>::myhash(const HashedObj &x) const {
    static hash<HashedObj> hf;
    return hf(x) % array.size();
}

template<typename HashedObj>
bool LinearProbingHashTable<HashedObj>::isActive(int pos) const {
    return array[pos].info == ACTIVE;
}

template<typename HashedObj>
void LinearProbingHashTable<HashedObj>::rehash() {
    std::vector<HashEntry> oldArray = array;

    array.resize(2 * oldArray.size());
    for (auto &entry : array)
        entry.info = EMPTY;

    currentSize = 0;
    for (auto &entry : oldArray)
        if (entry.info == ACTIVE)
            insert(std::move(entry.element));
}

template<typename HashedObj>
int LinearProbingHashTable<HashedObj>::nextPrime(int N) {
    if (N % 2 == 0)
        ++N;
    for (;; N += 2) {
        bool notPrime = false;
        for (int i = 3; i * i < N; i += 2) {
            if (N % i == 0) {
                notPrime = true;
                break;
            }
        }
        if (!notPrime) {
            return N;
        }
    }
}