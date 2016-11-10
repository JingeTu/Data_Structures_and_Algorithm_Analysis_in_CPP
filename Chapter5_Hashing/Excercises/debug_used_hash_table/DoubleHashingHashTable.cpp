//
// Created by 涂金戈 on 09/11/2016.
//

#include "DoubleHashingHashTable.h"

template<typename HashedObj>
DoubleHashingHashTable<HashedObj>::DoubleHashingHashTable(int size):array(nextPrime(size)) {
    makeEmpty();
}

template<typename HashedObj>
void DoubleHashingHashTable<HashedObj>::makeEmpty() {
    currentSize = 0;
    for (auto &entry : array)
        entry.info = EMPTY;
}

template<typename HashedObj>
bool DoubleHashingHashTable<HashedObj>::contains(const HashedObj &x) const {
    return isActive(findPos(x));
}

template<typename HashedObj>
bool DoubleHashingHashTable<HashedObj>::isActive(int pos) const {
    return array[pos].info == ACTIVE;
}

template<typename HashedObj>
int DoubleHashingHashTable<HashedObj>::findPos(const HashedObj &x) {
    int currentPos = myhash(x);

    if (array[currentPos].info == ACTIVE)
        return currentPos;

    int hash2Val = myhash2(x);

    while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
        currentPos += hash2Val;

        ++debug_collisionsNum;

        if (currentPos >= array.size())
            currentPos -= array.size();
    }

    return currentPos;
}

template<typename HashedObj>
bool DoubleHashingHashTable<HashedObj>::insert(const HashedObj &x) {
    int currenetPos = findPos(x);
    if (isActive(currenetPos))
        return false;

    array[currenetPos].element = x;
    array[currenetPos].info = ACTIVE;

    if (++currentSize >= array.size() / 2)
        rehash();

    return true;
}

template<typename HashedObj>
bool DoubleHashingHashTable<HashedObj>::insert(HashedObj &&x) {
    return insert(x);
}

template<typename HashedObj>
bool DoubleHashingHashTable<HashedObj>::remove(const HashedObj &x) {
    int currentPos = findPos(x);

    if (!isActive(currentPos))
        return false;

    array[currentPos].info = DELETED;

    return true;
}

template<typename HashedObj>
int DoubleHashingHashTable<HashedObj>::myhash(const HashedObj &x) const {
    static hash<HashedObj> hf;
    return hf(x) % array.size();
}

template<typename HashedObj>
int DoubleHashingHashTable<HashedObj>::myhash2(const HashedObj &x) const {
    static hash2<HashedObj> hf2;
    return hf2(x) % array.size();
}

template<typename HashedObj>
void DoubleHashingHashTable<HashedObj>::rehash() {
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
int DoubleHashingHashTable<HashedObj>::nextPrime(int N) {
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

template<typename HashedObj>
bool DoubleHashingHashTable<HashedObj>::debug_setCollisionsNum(const int &num) {
    debug_collisionsNum = num;
    return true;
}

template<typename HashedObj>
int DoubleHashingHashTable<HashedObj>::debug_getCollisionsNum() {
    return debug_collisionsNum;
}