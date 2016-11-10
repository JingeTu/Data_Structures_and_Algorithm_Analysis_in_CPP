//
// Created by 涂金戈 on 09/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_SEPARATECHAININGHASHTABLE_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_SEPARATECHAININGHASHTABLE_H

#include <string>
#include <vector>
#include <list>
#include "../../hash.h"

template<typename HashedObj>
class SeparateChainingHashTable {
public:
    explicit SeparateChainingHashTable(int size = 101);

    bool contains(const HashedObj &x) const;

    void makeEmpty();

    bool insert(const HashedObj &x);

    bool insert(const HashedObj &&x);

    bool remove(const HashedObj &x);

private:
    std::vector<std::list<HashedObj>> theLists;
    int currentSize;

    void rehash();

    size_t nextPrime(size_t N);

    size_t myhash(const HashedObj &x) const;
};

#include "SeparateChainingHashTable.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_SEPARATECHAININGHASHTABLE_H
