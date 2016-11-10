//
// Created by 涂金戈 on 09/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_QUADRATICPROBINGHASHTABLE_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_QUADRATICPROBINGHASHTABLE_H

#include <vector>
#include "hash.h"

template<typename HashedObj>
class QuadraticProbingHashTable {
public:
    explicit QuadraticProbingHashTable(int size = 101);

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

        HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY) : element{e}, info{i} {}

        HashEntry(HashedObj &&e, EntryType i = EMPTY) : element{std::move(e)}, info{i} {}
    };

    std::vector<HashEntry> array;
    int currentSize;

    int debug_collisionsNum;

    bool isActive(int currentPos) const;

    int findPos(const HashedObj &x) const;

    void rehash();

    size_t nextPrime(size_t N);

    size_t myhash(const HashedObj &x) const;
};

#include "QuadraticProbingHashTable.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_QUADRATICPROBINGHASHTABLE_H
