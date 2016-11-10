//
// Created by 涂金戈 on 09/11/2016.
//

#include "SeparateChainingHashTable.h"

template<typename HashedObj>
SeparateChainingHashTable<HashedObj>::SeparateChainingHashTable(int size): theLists(nextPrime(size)) {

}

template<typename HashedObj>
size_t SeparateChainingHashTable<HashedObj>::myhash(const HashedObj &x) const {
    static hash<HashedObj> hf;
    return hf(x) % theLists.size();
}

template<typename HashedObj>
bool SeparateChainingHashTable<HashedObj>::contains(const HashedObj &x) const {
    auto &whichList = theLists[myhash(x)];
    return std::find(std::begin(whichList), std::end(whichList), x) != std::end(whichList);
}

template<typename HashedObj>
void SeparateChainingHashTable<HashedObj>::makeEmpty() {
    for (std::list<HashedObj> &theList : theLists)
        theList.clear();
}

template<typename HashedObj>
bool SeparateChainingHashTable<HashedObj>::insert(const HashedObj &x) {
    auto &whichList = theLists[myhash(x)];
    if (std::find(std::begin(whichList), std::end(whichList), x) != std::end(whichList))
        return false;
    whichList.push_back(x);

    if (++currentSize > theLists.size()) // load factor is 1
        rehash();

    return true;
}

template<typename HashedObj>
bool SeparateChainingHashTable<HashedObj>::insert(const HashedObj &&x) {
    return insert(std::move(x));
}

template<typename HashedObj>
bool SeparateChainingHashTable<HashedObj>::remove(const HashedObj &x) {
    auto &whichList = theLists[myhash(x)];
    auto itr = std::find(std::begin(whichList), std::end(whichList), x);

    if (itr == std::end(whichList))
        return false;

    whichList.erase(itr);
    --currentSize;
    return true;
}

template<typename HashedObj>
void SeparateChainingHashTable<HashedObj>::rehash() {
    std::vector<std::list<HashedObj>> oldLists = theLists;

    theLists.resize(nextPrime(2 * oldLists.size()));
    for (auto &thisList : theLists)
        thisList.clear();

    currentSize = 0;
    for (auto &thisOldList : oldLists)
        for (auto &x : thisOldList)
            insert(std::move(x));
}

template<typename HashedObj>
size_t SeparateChainingHashTable<HashedObj>::nextPrime(size_t N) {
    if (N % 2 == 0)
        ++N;
    for (;; N += 2) {
        // if N is a prime return
        bool notPrime = false;
        for (size_t i = 3; i * i < N; ++i)
            if (N % i == 0) {
                notPrime = true;
                break;
            }
        if (!notPrime)
            return N;
    }
}