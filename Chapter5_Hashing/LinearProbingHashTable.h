//
// Created by 涂金戈 on 09/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_LINEARPROBINGHASHTABLE_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_LINEARPROBINGHASHTABLE_H

#include "hash.h"
#include <vector>

template<typename HashedObj>
class LinearProbingHashTable {
public:

    LinearProbingHashTable(int size = 101);

    bool contains(const HashedObj &x) const;

    void makeEmpty();

    bool insert(const HashedObj &x);

    bool insert(HashedObj &&x);

    bool remove(const HashedObj &x);

    int debug_getCollisionsNum();

    bool debug_setCollisionsNum(const int &num = 0);

    enum EntryType {
        ACTIVE, EMPTY, DELETED
    };

    struct HashEntry {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj &e = HashedObj{}, const EntryType &i = EMPTY) : element{e}, info{i} {}

        HashEntry(HashedObj &&e, const EntryType &i = EMPTY) : element{std::move(e)}, info{i} {}
    };

private:
    std::vector<HashEntry> array;
    int currentSize;

    int debug_collisionsNum;

    void rehash();

    int findPos(const HashedObj &x) const;

    bool isActive(int pos) const;

    static int nextPrime(int N);

    int myhash(const HashedObj &x) const;
};

#include "LinearProbingHashTable.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_LINEARPROBINGHASHTABLE_H
