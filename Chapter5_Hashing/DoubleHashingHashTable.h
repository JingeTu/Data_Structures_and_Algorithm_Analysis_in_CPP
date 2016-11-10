//
// Created by 涂金戈 on 09/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_DOUBLEHASHINGHASHTABLE_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_DOUBLEHASHINGHASHTABLE_H

#include "hash.h"
#include <vector>

template<typename HashedObj>
class DoubleHashingHashTable {
public:

    DoubleHashingHashTable(int size = 101);

    bool contains(const HashedObj &x) const;

    void makeEmpty();

    bool insert(const HashedObj &x);

    bool insert(HashedObj &&x);

    bool remove(const HashedObj &x);

    int debug_getCollisionsNum();

    bool debug_setCollisionsNum(const int &num = 0);

private:

    enum EntryType {
        ACTIVE, EMPTY, DELETED
    };

    struct HashEntry {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj &e = HashedObj{}, const EntryType &i = EMPTY) : element{e}, info{i} {}

        HashEntry(HashedObj &&e, const EntryType &i = EMPTY) : element{std::move(e)}, info{i} {}
    };

    std::vector<HashEntry> array;
    int currentSize;

    int debug_collisionsNum;

    void rehash();

    int findPos(const HashedObj &x) const;

    bool isActive(int pos) const;

    static int nextPrime(int N);

    int myhash(const HashedObj &x) const;

    int myhash2(const HashedObj &x) const;
};

#include "DoubleHashingHashTable.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_DOUBLEHASHINGHASHTABLE_H
