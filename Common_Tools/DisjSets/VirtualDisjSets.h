//
// Created by 涂金戈 on 27/12/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_VIRTUALDISJSETS_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_VIRTUALDISJSETS_H

#include <iostream>
#include <vector>

class VirtualDisjSets {
public:

    VirtualDisjSets(const int &element_num) : s(element_num, -1) {}

    bool SameSet(const int &e1, const int &e2) const;

    void UnionSets(const int &e1, const int &e2);

    void Print() const;

protected:

    int Find(const int &e) const;

    virtual void UnionSetsHelper(const int &root1, const int &root2) = 0;

    std::vector<int> s;
};

#include "VirtualDisjSets.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_VIRTUALDISJSETS_H
